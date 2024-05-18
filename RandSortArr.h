//�����:�������� �.�.
#pragma once
#include <cassert>
// ��������� ������� ��� ���������� ������� ������������ �������� � �������
template<typename T>
int find_min_index(const T* arr, size_t N) {
    T min_value = arr[0]; // ��������� ����������� �������� - ������ ������� �������
    for (size_t i = 1; i < N; ++i) { // �������� �� ���� ��������� �������
        if (arr[i] < min_value) { // ���� ������� ������� ������ ������������
            min_value = arr[i]; // ��������� ����������� ��������
        }
    }
    return min_value; // ���������� ������ ������������ ��������
}

// todo: another rand

// ��������� ������� ��� ��������� ���������� �������
template<typename T>
T* get_random_array(T* arr, size_t n, T from, T to) {
    for (size_t i = 0; i < n; ++i) { // ���������� ��� ��������
        arr[i] = from + (rand() % (to - from + 1)); // ���������� ��������� ����� � �������� ���������
    }
    return arr; // ���������� ��������� �� ������
}

// ��������� ������� ��� ��������� ���������� ������� �� �����������
template<typename T>
T* get_random_array_increase(T* arr, size_t n, T from, T to) {
    arr[0] = from + (rand() % (to - from + 1)); // ���������� ������ �������
    for (size_t i = 1; i < n; ++i) { // ���������� ����������� ��������
        arr[i] = arr[i - 1] + (rand() % ((to - arr[i - 1]))); // ����������� ���������� ������� ������������ �������� � ��������� �������� ���������
    }
    return arr; // ���������� ��������� �� ������
}

// ��������� ������� ��� ������ ������� � ����

/// <summary>
/// ������� ������ � ����
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="arr"> ������</param>
/// <param name="n"> ���-�� ���������</param>
/// <param name="filename"> �������� ����������</param>
template<typename T>
void write_arr_to_file(const T* arr, size_t n, const char* filename) {
    std::ofstream outFile(filename); // ��������� ���� ��� ������
    assert(outFile.is_open() && "���������� ������� ���� ��� ������."); // ���������, ��� ���� ������� ������
    for (size_t i = 0; i < n; ++i) { // ���������� ������ ������� ������� � ����
        outFile << arr[i] << " ";
    }
    outFile.close(); // ��������� ����
    std::cout << "������ ������� ������� � ����: " << filename << std::endl; // ������� ��������� �� �������� ������
}

// todo: ����������� ��������������
// ��������� ������� ��� ��������, ������������ �� ������ ???

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="arr"></param>
/// <param name="size"></param>
/// <returns></returns>
template<typename T>
bool is_sorted(T* arr, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        if (arr[i] < arr[i - 1]) {
            return false; // ���� ������� ������� ������ �����������, ������ �� ������������
        }
    }
    return true; // ���� �� ������ ���� ������ � �� ����� �� ������ ��������, ������� ������ �����������, ������ ������������
}
//����������� �������
// ��������� ������� ��� ��������, ������������ �� ������
template <typename Array>
bool arr_is_sort(const Array* arr, size_t size, std::string order = "ascending")
{
    // ���� � ������� 1 ��� 0 ���������, ���������� true
    if (size == 0 || size == 1)
        return true;

    // �������� �� ���� ��������� �������
    for (size_t i = 0; i < size - 1; i++)
    {
        // � ����������� �� ���������� ������� ����������
        switch (order)
        {
            // ���� ������� "ascending" (�� �����������)
        case "ascending":
            // ���� ������� ������� ������ ����������, ������ �� ������������ �� �����������
            if (arr[i] > arr[i + 1])
                return false;
            break;
            // ���� ������� "descending" (�� ��������)
        case "descending":
            // ���� ������� ������� ������ ����������, ������ �� ������������ �� ��������
            if (arr[i] < arr[i + 1])
                return false;
            break;
            // ���� ������� ���-�� ������
        default:
            // ������� ��������� �� ������
            std::cout << "Invalid order. Please choose either 'ascending' or 'descending'.\n";
            return false;
        }
    }
    // ���� �� ������ ���� ������ � �� ����� �� ������ ��������, ������� ������ (��� �����������) ��� ������ (��� ��������) ����������, ������ ������������
    return true;
}
