#pragma once

namespace Sine {

    namespace Sorting {

        template<class T, typename Comp>
        void InsertionSort(T *start, T *end, Comp func) {
            for (T *i = start + 1; i != end; i++) {
                T tem = *i, *j;
                for (j = i; j != start; j--) {
                    if (0 < (*func)(j - 1, &tem)) break;
                    *j = *(j - 1);
                }
                *j = tem;
            }
        }

        template<class T, typename Comp>
        void ShellSort(T *start, T *end, Comp func) {
            size_t k[30], size = end - start, len = 1;
            k[0] = 1, k[1] = 3;
            while (k[len] < size)
                k[++len] = k[len - 1] * 2 + len;
            for (size_t index = len; index != 0; index--) {
                size_t increment = k[index - 1];
                for (T *i = start + increment; i != end; i++) {
                    T tem = *i, *j;
                    for (j = i; j - increment >= start; j -= increment) {
                        if (0 < (*func)(j - increment, &tem)) break;
                        *j = *(j - increment);
                    }
                    *j = tem;
                }
            }
        }

        template<class T, typename Comp>
        void SelectionSort(T *start, T *end, Comp func) {
            for (T *i = start; i != end - 1; i++) {
                T *fore = i;
                for (T *j = i + 1; j != end; j++)
                    if (0 < (*func)(j, fore))
                        fore = j;
                T tem = *i;
                *i = *fore;
                *fore = tem;
            }
        }

        template<class T, typename Comp>
        void BubbleSort(T *start, T *end, Comp func) {
            for (T *i = start; i != end - 1; i++)
                for (T *j = end - 1; j != i; j--)
                    if (0 < (*func)(j, j - 1)) {
                        T tem = *(j - 1);
                        *(j - 1) = *j;
                        *j = tem;
                    }
        }

        template<class T, typename Comp>
        void MergeSort(T *start, T *end, Comp func) {
            T *tem = new T[end - start];
            MergeSortRecursion(start, end, tem, func);
            delete[] tem;
        }

        template<class T, typename Comp>
        void MergeSortRecursion(T *start, T *end, T *tem, Comp func) {
            if (end - start <= 1) return;
            size_t length = end - start, half = length / 2;
            MergeSortRecursion(start, start + half, tem, func);
            MergeSortRecursion(start + half, end, tem, func);
            T *cur = tem, *cur1 = start, *end1 = start + half, *cur2 = end1;
            while (cur1 != end1 && cur2 != end) {
                if (0 < (*func)(cur1, cur2))
                    *cur++ = *cur1++;
                else
                    *cur++ = *cur2++;
            }
            while (cur1 != end1)
                *cur++ = *cur1++;
            while (cur2 != end)
                *cur++ = *cur2++;
            while (start != end)
                *start++ = *tem++;
        }

        template<class T, typename Comp>
        void QuickSort(T *start, T *end, Comp func) {
            if (end - start < 2) return;
            T *x = end - 1, *cur = start;
            while (cur != x && 0 < (*func)(cur, x))
                cur++;
            T tem;
            for (T *i = cur + 1; i < x; i++) {
                if (0 < (*func)(i, x)) {
                    tem = *i;
                    *i = *cur;
                    *cur++ = tem;
                }
            }
            if (cur != x) {
                tem = *x;
                *x = *cur;
                *cur = tem;
            }
            QuickSort(start, cur, func);
            QuickSort(cur + 1, end, func);
        }

        template<class T, typename Comp>
        void HeapSort(T *start, T *end, Comp func) {
            if (end - start < 2)
                return;
            size_t i, j, k, length = end - start;
            T *r, *c, *t = start + 1, tem;
            // Ô¤´¦Àí
            for (i = 1; i < length; i++) {
                j = i;
                do {
                    k = (j - 1) / 2;
                    c = start + j, r = start + k;
                    if (0 < (*func)(c, r))
                        break;
                    tem = *r;
                    *r = *c;
                    *c = tem;
                    j = k;
                } while (k != 0);
            }
            while (start + 1 != end) {
                tem = *--end;
                *end = *start;
                *start = tem;
                i = 0;
                while (1) {
                    r = start + i, c = start + i * 2 + 1;
                    if (c + 1 < end && 0 < (*func)(c, c + 1))
                        c++;
                    if (c >= end || 0 < (*func)(c, r))
                        break;
                    tem = *r;
                    *r = *c;
                    *c = tem;
                    i = c - start;
                }
            }
        }
        
    }

}