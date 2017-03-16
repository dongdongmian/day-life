### 

**swap**
```
void swap(char &a, char &b){
    a = a^b;
    b = a^b;
    a = a^b;
}
```