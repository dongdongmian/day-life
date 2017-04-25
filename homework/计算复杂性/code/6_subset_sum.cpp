#include <iostream>
#include <cstring>

using namespace std;

int Answer;
int N;
int Value;
long long dyn[391];

int main(int argc, char** argv)
{
    int T, test_case;

    // freopen("input.txt", "r", stdin);

    cin >> T;
    for (test_case = 0; test_case < T; test_case++)
    {
        memset(dyn, 0, sizeof(dyn));

        Answer = 0;
        Value = 0;
        cin >> N;

        Value = N*(N + 1);
        if (Value % 4)
        {
            // Print the answer to standard output(screen).
            cout << "Case #" << test_case + 1 << endl;
            cout << 0 << endl;
            continue;
        }

        Value /= 4;

        dyn[0] = 1;

        for (int i = 1; i <= N; i++)
        {
            for (int j = Value; j >= i; j--)
            {
                dyn[j] = dyn[j] + dyn[j - i];
            }
        }

        // Print the answer to standard output(screen).
        cout << "Case #" << test_case + 1 << endl;
        cout << dyn[Value]/2 << endl;
    }

    return 0;//Your program should return 0 on normal termination.
}
