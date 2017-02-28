#!/usr/bin/env python
import sys

reload(sys)
sys.setdefaultencoding('utf8')

import requests
from bs4 import BeautifulSoup
import re
import time
import pymysql

# global data
# url:website
# raw_cookies:personnal cookie
url = "http://www.myhuiban.com/conferences?Conference_page="
# url_info = "http://www.myhuiban.com"
url_info = "http://www.myhuiban.com"

headers = {
    'Host': 'www.myhuiban.com',
    'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:46.0) Gecko/20100101 Firefox/46.0',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
    'Accept-Language': 'en-US,en;q=0.5',
    'Accept-Encoding': 'gzip, deflate',
    'Referer': 'http://www.myhuiban.com/login',
    'Connection': 'keep-alive',
}

raw_cookies = '''__utma=201260338.1054709214.1487766959.1487848204.1487852132.8;__utmz=201260338.1487766961.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); PHPSESSID=3ed9ad207a0a3d9f62e730721efa36c1; __utmb=201260338.14.10.1487852132; __utmc=201260338;cb813690bb90b0461edd205fc53b6b1c=3573b25ca5a337adcaa1f3a8d9ea87fac80d7163a%3A4%3A%7Bi%3A0%3Bs%3A17%3A%221443222081%40qq.com%22%3Bi%3A1%3Bs%3A17%3A%221443222081%40qq.com%22%3Bi%3A2%3Bi%3A2592000%3Bi%3A3%3Ba%3A3%3A%7Bs%3A2%3A%22id%22%3Bs%3A4%3A%227281%22%3Bs%3A4%3A%22name%22%3Bs%3A9%3A%22dong+mian%22%3Bs%3A4%3A%22type%22%3Bs%3A1%3A%22n%22%3B%7D%7D'''

conn = pymysql.connect(host='127.0.0.1',user='root',port=3306,passwd='6673267nm')

# data_list[] save all of the data we want
# head_list[] save the table first line
# head_list = []
data_list = []

# get cookie
def get_cookie():
    cookies={}
    for line in raw_cookies.split(';'):
        key,value=line.split('=',1)
        key = key.strip()
        value = value.strip()
        cookies[key]=value
    # print cookies
    return cookies

#save data to file
def write_data(file_name,mode,content):
    with open(file_name, mode) as fp:
        fp.write(content)
        fp.close()

# get one page
# url:
def get_page(pageURL):
    r = requests.get(pageURL, cookies=get_cookie(), headers=headers)
    return r


# get the web infomation
def get_data(url0):
    r = get_page(url0)

    soup = BeautifulSoup(r.text,'lxml')
    yw2 = soup.find(id='yw2')

    record = 0
    for record, tr in enumerate(yw2.find_all('tr')):
        # get the table first line

        # if record == 0:
        #     ths = tr.find_all('th')
        #     for th in ths:
        #         # print(th.contents[0])
        #         head_list.append(th.contents)

        if record != 0:
            for i, td in enumerate(tr.find_all('td')):
                if ( i==0 or i==1 or i==2):
                    rank = re.findall(r"\>(.*?)\<",str(td.contents))
                    data_list.append(rank)
                elif i == 4:
                    href = re.findall(r"href=\"(.*?)\"",str(td.contents))
                    href = url_info+href[0]
                    head = re.findall(r"\>(.*?)\<",str(td.contents))
                    data_list.append(href)
                    data_list.append(head[0])
                elif i == 5:
                    extends = re.findall(r"<small>(.*?)</small>",str(td.contents))
                    data_list.append(extends)
                elif ( i==10 or i==11 ):
                    no = re.findall(r"\>(.*?)\<",str(td.contents))
                    data_list.append(no)
                else:
                    data_list.append(td.contents)

    # print(record)
    # print(head_list)
    # print(data_list)
    return record


# recreate the table , and over all of the data
def reset_db():

    # add all of the website data to the table
    result_sum = 0
    record = 0
    i = 1

    print("---------------------------------------------------")

    # <20 data is the last website,because there has 'past event' ,so can not use the 0
    record = get_data(url+str(i))
    while  (record == 20):
        result_sum = result_sum + record
        i = i + 1
        record = get_data(url+str(i))
        print(i)
    result_sum = result_sum + record


    cur = conn.cursor()
    cur.execute("create database if not exists myhuiban")
    conn.select_db("myhuiban")

    cur.execute("drop table if exists conference")
    # create the table
    cur.execute("create table if not exists conference(\
        ccf varchar(4),\
        core varchar(4),\
        qualis varchar(4),\
        short varchar(20),\
        link varchar(100),\
        full_name varchar(200),\
        extended varchar(10),\
        submission varchar(20),\
        notification varchar(20),\
        conference varchar(20),\
        location varchar(50),\
        years varchar(20),\
        viewed varchar(20),\
        primary key(full_name,conference))"
        )

    print(result_sum)

    for i in range(result_sum):
        idx = 13*i

        # print("-------------------------------------------")

        for j in range(13):
            if len(data_list[idx+j]) == 0:
                data_list[idx+j] = ['NULL']
            # data_list[idx+j][0].encode('utf-8')
            # print(data_list[idx+j])

        a = cur.execute("INSERT INTO conference VALUES(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)",\
            (str(data_list[idx][0]),str(data_list[idx+1][0]),str(data_list[idx+2][0]),str(data_list[idx+3][0]),\
            data_list[idx+4],data_list[idx+5],str(data_list[idx+6][0]),\
            str(data_list[idx+7][0]),str(data_list[idx+8][0]),str(data_list[idx+9][0]),\
            str(data_list[idx+10][0]),str(data_list[idx+11][0]),str(data_list[idx+12][0]) ) )
        # print(a)

    conn.commit()

    # test if data write to the database

    # b = cur.execute("SELECT * FROM conference WHERE ccf = 'a' ")
    # print(b)
    # print(cur.fetchall())

    cur.close()
    # conn.close()



# link database
#result_sum:all of the data records
def update_db():

    # get one page to update the database
    j = 0
    record = 0

    cur = conn.cursor()
    conn.select_db("myhuiban")

    record = get_data(url+str(j))
    while record != 0:
        j = j + 1
        record = get_data(url+str(j))
        print(record)

        # if database have not the record , update the record to the database,,else record = 0,break the while
        for i in range(record):
            idx = 13*i

            a = cur.execute("SELECT * FROM conference WHERE full_name = %s AND conference = %s",( data_list[idx+5] , str(data_list[idx+9][0]) ) )
            # a = cur.execute("SELECT * FROM conference WHERE full_name = %s",( data_list[idx+5] ) )
            print('a=%d',a)
            if a == 0:

                for k in range(13):
                        if len(data_list[idx+k]) == 0:
                            data_list[idx+k] = ['NULL']

                b = cur.execute("INSERT INTO conference VALUES(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)",\
                    (str(data_list[idx][0]),str(data_list[idx+1][0]),str(data_list[idx+2][0]),str(data_list[idx+3][0]),\
                    data_list[idx+4],data_list[idx+5],str(data_list[idx+6][0]),\
                    str(data_list[idx+7][0]),str(data_list[idx+8][0]),str(data_list[idx+9][0]),\
                    str(data_list[idx+10][0]),str(data_list[idx+11][0]),str(data_list[idx+12][0]) ) )

                print(b)
            else:
                record = 0
                break

    conn.commit()
    cur.close()





# recreate the table
# reset_db()

update_db()
conn.close()
