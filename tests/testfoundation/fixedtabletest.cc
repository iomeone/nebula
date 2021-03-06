//------------------------------------------------------------------------------
//  fixedtabletest.cc
//  (C) 2006 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "fixedtabletest.h"
#include "util/fixedtable.h"

namespace Test
{
__ImplementClass(Test::FixedTableTest, 'FTBT', Test::TestCase);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
void
FixedTableTest::Run()
{
    const SizeT w = 4;
    const SizeT h = 3;
    FixedTable<int> table(w, h, 7);
    
    // verify correct construction
    VERIFY(table.Width() == w);
    VERIFY(table.Height() == h);
    IndexT y, x;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            VERIFY(table.At(x, y) == 7);
        }
    }

    // fill with values and verify contents
    int val = 0;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            table.Set(x, y, val++);
        }
    }
    val = 0;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            VERIFY(table.At(x, y) == val);
            val++;
        }
    }

    // build another table as copy of the first one
    FixedTable<int> copy = table;
    VERIFY(copy == table);
    VERIFY(!(copy != table));
    copy.At(3, 1) = 23;
    VERIFY(copy != table);
    VERIFY(!(copy == table));

    copy.SetSize(2, 2);
    VERIFY(copy.Width() == 2);
    VERIFY(copy.Height() == 2);
    copy.Clear(3);
    VERIFY(copy.At(0, 0) == 3);
    VERIFY(copy.At(0, 1) == 3);
    VERIFY(copy.At(1, 0) == 3);
    VERIFY(copy.At(0, 1) == 3);
    VERIFY(copy != table);
    VERIFY(!(copy == table));
}

} // namespace Test
