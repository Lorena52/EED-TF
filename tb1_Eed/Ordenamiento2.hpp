#pragma once
#include <vector>
using namespace std;

// ===============================================================
//  ORDENAMIENTO2.hpp - MergeSort y QuickSort
//  Trabajan sobre vector<T> con comparador bool (*menor)(T, T)
// ===============================================================

// ---------------------------------------------------------------
//  MERGE SORT  -  O(n log n), estable.
// ---------------------------------------------------------------
template <typename T>
void mezclar2(vector<T>& v, int izq, int medio, int der, bool (*menor)(T, T)) {
    vector<T> temp;
    int i = izq, j = medio + 1;
    while (i <= medio && j <= der) {
        if (menor(v[i], v[j])) temp.push_back(v[i++]);
        else                   temp.push_back(v[j++]);
    }
    while (i <= medio) temp.push_back(v[i++]);
    while (j <= der)   temp.push_back(v[j++]);
    for (int k = 0; k < (int)temp.size(); k++) v[izq + k] = temp[k];
}

template <typename T>
void mergeSort(vector<T>& v, int izq, int der, bool (*menor)(T, T)) {
    if (izq >= der) return;
    int medio = (izq + der) / 2;
    mergeSort(v, izq, medio, menor);
    mergeSort(v, medio + 1, der, menor);
    mezclar2(v, izq, medio, der, menor);
}

// Atajo: ordena todo el vector
template <typename T>
void mergeSort(vector<T>& v, bool (*menor)(T, T)) {
    if (!v.empty()) mergeSort(v, 0, (int)v.size() - 1, menor);
}

// ---------------------------------------------------------------
//  QUICK SORT  -  O(n log n) promedio.
// ---------------------------------------------------------------
template <typename T>
int particionar2(vector<T>& v, int izq, int der, bool (*menor)(T, T)) {
    T pivote = v[der];
    int i = izq - 1;
    for (int j = izq; j < der; j++) {
        if (menor(v[j], pivote)) { i++; swap(v[i], v[j]); }
    }
    swap(v[i + 1], v[der]);
    return i + 1;
}

template <typename T>
void quickSort(vector<T>& v, int izq, int der, bool (*menor)(T, T)) {
    if (izq >= der) return;
    int p = particionar2(v, izq, der, menor);
    quickSort(v, izq, p - 1, menor);
    quickSort(v, p + 1, der, menor);
}

// Atajo: ordena todo el vector
template <typename T>
void quickSort(vector<T>& v, bool (*menor)(T, T)) {
    if (!v.empty()) quickSort(v, 0, (int)v.size() - 1, menor);
}