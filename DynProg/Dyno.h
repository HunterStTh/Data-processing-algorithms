//�����:�������� �.�
#pragma once
#ifndef DYNO_H
#define DYNO_H

//�-��� ��������� � ���������� ����� N ������, ���������� ���-�� ���������� ������
int SafetyCase(int N);

//����� SafetyCase
void test_safety_case();

// ������� ��� ������ ������ �� �����
int fromFile(const std::string &filename);

#endif