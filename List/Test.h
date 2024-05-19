#pragma once
#include"List.h"
#include <cassert>

void test() {
    DoublyLinkedList<int> list;

    // ������������ ������ insert_end
    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    assert(list.get_size() == 3);
    assert(list.get_at(0) == 1);
    assert(list.get_at(1) == 2);
    assert(list.get_at(2) == 3);

    // ������������ ������ insert_begin
    list.insert_begin(0);
    assert(list.get_size() == 4);
    assert(list.get_at(0) == 0);
    assert(list.get_at(1) == 1);
    assert(list.get_at(2) == 2);
    assert(list.get_at(3) == 3);

    // ������������ ������ insert_after
    list.insert_after(2, 3);
    assert(list.get_size() == 5);
    assert(list.get_at(0) == 0);
    assert(list.get_at(1) == 1);
    assert(list.get_at(2) == 2);
    assert(list.get_at(3) == 3);

    // ������������ ������ insert_at
    list.insert_at(0, -1);
    assert(list.get_size() == 6);
    assert(list.get_at(0) == -1);
    assert(list.get_at(1) == 0);
    assert(list.get_at(2) == 1);
    assert(list.get_at(3) == 2);
    assert(list.get_at(4) == 3);

    // ������������ ������ remove
    assert(list.remove(3) == true);
    assert(list.get_size() == 5);
    assert(list.get_at(0) == -1);
    assert(list.get_at(1) == 0);
    assert(list.get_at(2) == 1);
    assert(list.get_at(3) == 2);
    assert(list.remove(10) == false); // ������� ������� �������������� �������
    //throw, ���� ������ ����, at 1000 , ��� ������� �������
    // ������������ ������ clear
    list.clear();
    assert(list.get_size() == 0);
}
