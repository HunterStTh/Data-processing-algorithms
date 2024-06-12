//�����:�������� �.�

#include<vector>//��� ��������� ��������
#include <cassert>//��� ������
#include <fstream>//��� ������ � �������
#include <string>


/// ������� ��������� � ���������� ����� N ������, ���������� ���������� ���������� ������
int SafetyCase(int N)
{
    // ���� N ������ ��� ����� 0, ���������� 0
    if (N <= 0) return 0;

    // ������� ������ dp �������� N+1 ��� �������� ���������� ���������� ������ ��� ������� ����� �����������
    std::vector<size_t> dp(N + 1);

    // �������������� ������ ��� �������� ������� dp
    dp[0] = 1; // ���������� ������ ���� ���������� ������ �� 1 ����������� (������ ������)
    if (N >= 1) dp[1] = 2; // ���������� ��� ���������� ������ �� ������ ����������: A � B
    if (N >= 2) dp[2] = 4; // ���������� ������ ���������� ������ �� ���� �����������: AA, AB, BA � BB

    // ��� ������� i �� 3 �� N ��������� dp[i] ��� ����� dp[i-1], dp[i-2] � dp[i-3]
    for (int i = 3; i <= N; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }

    // ���������� ���������� ���������� ������ ��� N �����������
    return dp[N];
}

//����� SafetyCase
void test_safety_case() {
    assert(SafetyCase(0) == 0);//0
    assert(SafetyCase(1) == 2);//a,b
    assert(SafetyCase(2) == 4);//aa,ab,ba,bb
    assert(SafetyCase(3) == 7);//����� 8, �� 1 ������������
    assert(SafetyCase(4) == 13);//7+4+2
    assert(SafetyCase(-2) == 0);//incorrect
}

// ������� ��� ������ ������ �� �����
int fromFile(const std::string &filename) {
    std::ifstream file(filename); // ��������� ����

    if (!file) { // ���� ���� �� ������
        return -1;
    }

    int N;
    file >> N; // ��������� ����� �����������

    file.close(); // ��������� ����

    return N;
}