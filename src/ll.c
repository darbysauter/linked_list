#include "ll.h"
ll_node *ll_first(ll_node *n) { /*{{{*/
    if (n == nullptr) { return nullptr; }
    for (; n->prev!=nullptr; n=n->prev);
    return n;
} /*}}}*/
ll_node *ll_last(ll_node *n) { /*{{{*/
    if (n == nullptr) { return nullptr; }
    for (; n->next!=nullptr; n=n->next);
    return n;
} /*}}}*/
size_t ll_length(const ll_node *n) { /*{{{*/
    if (n == nullptr) { return 0; }
    size_t c = 0;
    while (n != nullptr) {
        ++c;
        n = n->next;
    }
    return c;
} /*}}}*/
ll_node *ll_insert_before(ll_node *n, void *data) { /*{{{*/
    ll_node *o = (ll_node *)malloc(sizeof(ll_node));
    if (o == nullptr) { return nullptr; }
    o->data = data;
    if (n == nullptr) { /*{{{*/
        o->prev = nullptr;
        o->next = nullptr;
    } /*}}}*/
    else { /*{{{*/
        if (n->prev != nullptr) {
            n->prev->next = o;
        }
        o->prev = n->prev;
        o->next = n;
        n->prev = o;
    } /*}}}*/
    return o;
} /*}}}*/
ll_node *ll_insert_after(ll_node *n, void *data) { /*{{{*/
    ll_node *o = (ll_node *) malloc(sizeof(ll_node));
    if (o == nullptr) { return nullptr; }
    o->data = data;
    if (n == nullptr) { /*{{{*/
        o->prev = nullptr;
        o->next = nullptr;
    } /*}}}*/
    else { /*{{{*/
        if (n->next != nullptr) {
            n->next->prev = o;
        }
        o->prev = n;
        o->next = n->next;
        n->next = o;
        if (n->prev == n) {
            n->prev = o;
        }
    } /*}}}*/
    return o;
} /*}}}*/
ll_node *ll_cut_before(ll_node *n) { /*{{{*/
    if (n == nullptr) {
        return nullptr;
    }
    ll_node *prev = n->prev;
    if (prev==nullptr) {
        return nullptr;
    }
    else {
        n->prev = nullptr;
        prev->next = nullptr;
        return prev;
    }
} /*}}}*/
ll_node *ll_cut_after(ll_node *n) { /*{{{*/
    if (n == nullptr) {
        return nullptr;
    }
    ll_node *next = n->next;
    if (next==nullptr) {
        return nullptr;
    }
    else {
        n->next = nullptr;
        next->prev = nullptr;
        return next;
    }
} /*}}}*/
void ll_glue(ll_node *prev, ll_node *next) { /*{{{*/
    if (prev != nullptr) {
        prev->next = next;
    }
    if(next != nullptr) {
        next->prev = prev;
    }
} /*}}}*/
ll_node *ll_find(ll_node *n, bool (*predicate)(void *)) { /*{{{*/
    for (; n!=nullptr; n=n->next) {
        if (predicate(n->data)) {
            return n;
        }
    }
    return nullptr;
} /*}}}*/
ll_node *ll_rfind(ll_node *n, bool (*predicate)(void *)) { /*{{{*/
    for (; n!=nullptr; n=n->prev) {
        if (predicate(n->data)) {
            return n;
        }
    }
    return nullptr;
} /*}}}*/
ll_node *ll_find_r(ll_node *n, bool (*predicate)(void *, void *), void *extra) { /*{{{*/
    for (; n!=nullptr; n=n->next) {
        if (predicate(n->data, extra)) {
            return n;
        }
    }
    return nullptr;
} /*}}}*/
ll_node *ll_rfind_r(ll_node *n, bool (*predicate)(void *, void *), void *extra) { /*{{{*/
    for (; n!=nullptr; n=n->prev) {
        if (predicate(n->data, extra)) {
            return n;
        }
    }
    return nullptr;
} /*}}}*/
void *ll_remove(ll_node *n) { /*{{{*/
    if (n == nullptr) { return nullptr; }
    if (n->prev != nullptr) {
        n->prev->next = n->next;
    }
    if (n->next != nullptr) {
        n->next->prev = n->prev;
    }
    void *data = n->data;
    free(n);
    return data;
} /*}}}*/
void ll_map(ll_node *n, void *(*func) (void*)) { /*{{{*/
    if (n == nullptr) { return; }
    for (; n!=nullptr; n=n->next) {
        n->data = func(n->data);
    }
} /*}}}*/
void ll_map_r(ll_node *n, void *(*func) (void*, void*), void *extra) { /*{{{*/
    for (; n!=nullptr; n=n->next) {
        n->data = func(n->data, extra);
    }
} /*}}}*/
void ll_nodemap(ll_node *n, ll_node *(*func) (ll_node *)) { /*{{{*/
    while (n != nullptr) {
        n = func(n);
    }
} /*}}}*/
void ll_nodemap_r(ll_node *n, ll_node *(*func) (ll_node *, void *), void *extra) { /*{{{*/
    while (n != nullptr) {
        n = func(n, extra);
    }
} /*}}}*/
void ll_destroy(ll_node *n) { /*{{{*/
    ll_cut_before(n);
    while (n != nullptr) {
        ll_node *o = n;
        n = n->next;
        free(o);
    }
} /*}}}*/
void ll_mapdestroy(ll_node *n, void (func) (void*)) { /*{{{*/
    ll_cut_before(n);
    while (n != nullptr) {
        ll_node *o = n;
        func(n->data);
        n = n->next;
        free(o);
    }
} /*}}}*/
void ll_mapdestroy_r(ll_node *n, void (func) (void*, void*), void *state) { /*{{{*/
    ll_cut_before(n);
    while (n != nullptr) {
        ll_node *o = n;
        func(n->data, state);
        n = n->next;
        free(o);
    }
} /*}}}*/
bool ll_is_circular(const ll_node *n) { /*{{{*/
	const ll_node *o = n;
	while (true) {
		if (n == nullptr) {
			return false;
		}
		n = n->next;
		if (n == o) {
			return true;
		}
	}
}/*}}}*/
size_t ll_clength(const ll_node *n) { /*{{{*/
	if (n == nullptr) { return 0; }
	size_t c = 0;
	const ll_node *o = n;
	do {
		++c;
		n = n->next;
	} while (n != o && n != nullptr);
	return c;
} /*}}}*/
ll_node *ll_cfind(ll_node *n, bool (*predicate)(void *)) { /*{{{*/
	if (n == nullptr) { return nullptr; }
	ll_node *o = n;
	do {
		if (predicate(n->data)) {
			return n;
		}
		n = n->next;
	} while (n != o && n != nullptr);
	return nullptr;
} /*}}}*/
ll_node *ll_crfind(ll_node *n, bool (*predicate)(void *)) { /*{{{*/
	if (n == nullptr) { return nullptr; }
	ll_node *o = n;
	do {
		if (predicate(n->data)) {
			return n;
		}
		n = n->prev;
	} while (n != o && n != nullptr);
	return nullptr;
} /*}}}*/
ll_node *ll_cfind_r(ll_node *n, bool (*predicate)(void *, void *), void *extra) { /*{{{*/
	if (n == nullptr) { return nullptr; }
	ll_node *o = n;
	do {
		if (predicate(n->data, extra)) {
			return n;
		}
		n = n->next;
	} while (n != o && n != nullptr);
	return nullptr;
} /*}}}*/
ll_node *ll_crfind_r(ll_node *n, bool (*predicate)(void *, void *), void *extra) { /*{{{*/
	if (n == nullptr) { return nullptr; }
	ll_node *o = n;
	do {
		if (predicate(n->data, extra)) {
			return n;
		}
		n = n->prev;
	} while (n != o && n != nullptr);
	return nullptr;
} /*}}}*/
void ll_cmap(ll_node *n, void *(*func) (void*)) { /*{{{*/
	if (n == nullptr) { return; }
	ll_node *o = n;
	do {
		n->data = func(n->data);
		n = n->next;
	} while (n != o && n != nullptr);
} /*}}}*/
void ll_cmap_r(ll_node *n, void *(*func) (void*, void*), void *extra) { /*{{{*/
	if (n == nullptr) { return; }
	ll_node *o = n;
	do {
		n->data = func(n->data, extra);
		n = n->next;
	} while (n != o && n != nullptr);
} /*}}}*/
