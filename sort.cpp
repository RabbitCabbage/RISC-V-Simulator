//
// Created by lu'ren'jia'd's on 2022/6/23.
//
#include "sort.hpp"

void merge(std::vector<int> &v, int l, int r, int mid) {
    //把两段排好序，一段l~mid 另一段mid+1~r
    long long tmp[r - l + 1];
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (query(v[j], v[i]))tmp[k++] = v[j++];
        else tmp[k++] = v[i++];
    }
    //k指向的是要放进去的空位子，ij指向要放的元素
    if (i == mid + 1)while (j <= r)tmp[k++] = v[j++];
    if (j == r + 1)while (i <= mid)tmp[k++] = v[i++];
    for (int p = 0, q = l; p < r - l + 1; p++, q++)
        v[q] = tmp[p];
}

void sort(std::vector<int> &v, int start, int end) {
    if (start >= end)return;
    int mid = (start + end) >> 1;
    sort(v, start, mid);
    sort(v, mid + 1, end);
    merge(v, start, end, mid);
}


std::vector<int> my_sort(int n) {
    std::vector<int> v;
    for (int i = 0; i < n; ++i)v.push_back(i);
    sort(v, 0, n - 1);
    return v;
}

