#ifndef OPPM_SCALE_OST_H
#define OPPM_SCALE_OST_H

#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef
tree<
        int,
        int,
        less<>,
        rb_tree_tag,
        tree_order_statistics_node_update
> ost;

#endif //OPPM_SCALE_OST_H
