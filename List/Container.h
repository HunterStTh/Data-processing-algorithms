//�����: �������� �.�.
#pragma once
// ������ ������ ��� ����������
template<typename T>
class Container {
public:
    // ����������� ������� ��� ��������, ������� ������ ���� ����������� � ����������� �������
    virtual void insert_begin(T data) = 0; // ������� �������� � ������
    virtual void insert_end(T data) = 0; // ������� �������� � �����
    virtual bool remove(T data) = 0; // �������� ��������
    virtual size_t get_size() = 0; // ��������� ������� ����������
};