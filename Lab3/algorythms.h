#ifndef INC_3_LAB_ALGORYTHMS_H
#define INC_3_LAB_ALGORYTHMS_H

template<class Iter, class Predicate>
bool all_of(Iter begin, Iter end, Predicate predicate) {
    for (begin; begin != end; begin++) {
        if (!predicate(*begin)) {
            return false;
        }
    }
    return true;
}

template<class Iter, class Predicate>
bool any_of(Iter begin, Iter end, Predicate predicate) {
    for (begin; begin != end; begin++) {
        if (predicate(*begin)) {
            return true;
        }
    }
    return false;
}

template<class Iter, class Predicate>
bool none_of(Iter begin, Iter end, Predicate predicate) {
    for (begin; begin != end; begin++) {
        if (predicate(*begin)) {
            return false;
        }
    }
    return true;
}

template<class Iter, class Predicate>
bool one_of(Iter begin, Iter end, Predicate predicate) {
    int cnt = 0;
    for (begin; begin != end; begin++) {
        if (predicate(*begin)) {
            cnt++;
        }
    }
    if (cnt == 1) {
        return true;
    } else {
        return false;
    }
}

template<class Iter, class Predicate>
bool is_sorted(Iter begin, Iter end, Predicate predicate) {
    Iter next = begin;
    while (++next != end) {
        if (!predicate(*next, *begin)) {
            return false;
        }
        begin = next;
    }
    return true;
}

template<class Iter, class Predicate>
bool is_partitioned(Iter begin, Iter end, Predicate predicate) {
    bool wasPartition = false;
    Iter next = begin;
    while (++next != end) {
        if (!predicate(*next, *begin)) {
            if (wasPartition) {
                return false;
            }
            wasPartition = true;
        }
        begin = next;
    }
    return wasPartition;
}

template<class Iter, class S>
Iter find_not(Iter begin, Iter end, S wanted) {

    for (begin; begin != end; begin++) {
        if (wanted != *begin) {
            return begin;
        }
    }
    return end;
}

template<class Iter, class S>
Iter find_backward(Iter begin, Iter end, S wanted) {
    for (end; begin != end; end--) {
        if (wanted == *end) {
            return end;
        }
    }
    return begin;
}

template<class Iter, class Predicate>
bool is_palindrome(Iter begin, Iter end, Predicate predicate) {
    Iter temp = end;
    while (begin != --end && begin != temp) {
        if (predicate(*end) != predicate(*begin)) {
            return false;
        }
        begin++;
    }
    return true;
}

#endif //INC_3_LAB_ALGORYTHMS_H
