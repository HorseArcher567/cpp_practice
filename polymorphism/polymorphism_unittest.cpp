//
// Created by yp on 2023/12/27.
//

#include <typeinfo>
#include <gtest/gtest.h>
#include "normal_inherit.h"
#include "virtual_inherit.h"
#include "function_overloading.h"
#include "function_hiding.h"

TEST(PolymorphismTest, NormalInherit) {
	/*
	 * (gdb) p *derived
	 * $6 = {
	 * 	<normal_inherit::BaseA> = {
	 * 		<normal_inherit::Base> = {
	 * 			_vptr$Base = 0x10007da48 <vtable for normal_inherit::Derived+16>,
	 * 			s = 10
	 * 		},
	 *    members of normal_inherit::BaseA:
	 *    a = 20
	 * 	},
	 * 	<normal_inherit::BaseB> = {
	 * 		<normal_inherit::Base> = {
	 * 			_vptr$Base = 0x10007da70 <vtable for normal_inherit::Derived+56>,
	 * 			s = 10
	 * 		},
	 * 		members of normal_inherit::BaseB:
	 * 		b = 30
	 * 		},
	 * 	<normal_inherit::BaseC> = {
	 * 		_vptr$BaseC = 0x10007da98 <vtable for normal_inherit::Derived+96>,
	 * 		c = 40
	 * 	},
	 * 	members of normal_inherit::Derived:
	 * 	d = 50
	 * }
	 */
	using namespace normal_inherit;
	auto *derived = new Derived();
	auto *addr = reinterpret_cast<uintptr_t *>(derived);

	// -----------------------------BaseA--------------------------------
	auto vptr = *reinterpret_cast<uintptr_t **>(derived);
	auto offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	std::cout << "BaseA offsetToTop: " << offsetToTop << std::endl;
	BaseA *pBaseA = derived;
	auto offset = reinterpret_cast<uintptr_t>(pBaseA) - reinterpret_cast<uintptr_t>(derived);
	EXPECT_EQ(offsetToTop, -offset);
	auto typeInfoName = reinterpret_cast<std::type_info *>(vptr[-1])->name();
	EXPECT_STREQ(typeInfoName, typeid(*derived).name());
	auto fooValue = reinterpret_cast<long (*)(Derived *)>(vptr[2])(derived);
	EXPECT_EQ(fooValue, derived->d);

	auto *s = addr + 1;
	EXPECT_EQ(*reinterpret_cast<long *>(s), derived->BaseA::s);

	auto *a = reinterpret_cast<uintptr_t *>(derived) + 2;
	EXPECT_EQ(*reinterpret_cast<long *>(a), derived->a);

	// ------------------------------BaseB--------------------------------
	vptr = *reinterpret_cast<uintptr_t **>(addr + 3);
	offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	std::cout << "BaseB offsetToTop: " << offsetToTop << std::endl;
	BaseB *pBaseB = derived;
	offset = reinterpret_cast<uintptr_t>(pBaseB) - reinterpret_cast<uintptr_t>(derived);
	EXPECT_EQ(offsetToTop, -offset);
	typeInfoName = reinterpret_cast<std::type_info *>(vptr[-1])->name();
	EXPECT_STREQ(typeInfoName, typeid(*derived).name());
	fooValue = reinterpret_cast<long (*)(BaseB *)>(vptr[2])(pBaseB);
	EXPECT_EQ(fooValue, derived->d);

	s = reinterpret_cast<uintptr_t *>(derived) + 4;
	EXPECT_EQ(*reinterpret_cast<long *>(s), derived->BaseB::s);

	auto *b = reinterpret_cast<uintptr_t *>(derived) + 5;
	EXPECT_EQ(*reinterpret_cast<long *>(b), derived->b);

	// ------------------------------BaseC--------------------------------
	vptr = *reinterpret_cast<uintptr_t **>(addr + 6);
	offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	std::cout << "BaseC offsetToTop: " << offsetToTop << std::endl;
	BaseC *pBaseC = derived;
	offset = reinterpret_cast<uintptr_t>(pBaseC) - reinterpret_cast<uintptr_t>(derived);
	EXPECT_EQ(offsetToTop, -offset);
	typeInfoName = reinterpret_cast<std::type_info *>(vptr[-1])->name();
	EXPECT_STREQ(typeInfoName, typeid(*derived).name());
	fooValue = reinterpret_cast<long (*)(BaseC *)>(vptr[2])(pBaseC);
	EXPECT_EQ(fooValue, derived->d);

	auto *c = reinterpret_cast<uintptr_t *>(derived) + 7;
	EXPECT_EQ(*reinterpret_cast<long *>(c), derived->c);

	auto *d = reinterpret_cast<uintptr_t *>(derived) + 8;
	EXPECT_EQ(*reinterpret_cast<long *>(d), derived->d);

	std::cout << "Ambiguity：" << std::endl;
	std::cout << "	derived->BaseA::s: " << derived->BaseA::s << std::endl;
	std::cout << "	derived->BaseB::s: " << derived->BaseB::s << std::endl;
	// 资源浪费
	auto *as = reinterpret_cast<uintptr_t *>(&derived->BaseA::s);
	auto *bs = reinterpret_cast<uintptr_t *>(&derived->BaseB::s);
	EXPECT_NE(as, bs);

	delete derived;
}

TEST(PolymorphismTest, VirtualInherit) {
	/*
	 * (gdb) p *derived
	 * $8 = {
	 * 	<virtual_inherit::BaseA> = {
	 * 		<virtual_inherit::Base> = {
	 * 			_vptr$Base = 0x10007dcf0 <vtable for virtual_inherit::Derived+168>,
	 * 			s = 10
	 * 		},
	 * 		members of virtual_inherit::BaseA:
	 * 		_vptr$BaseA = 0x10007dc60 <vtable for virtual_inherit::Derived+24>,
	 * 		a = 20
	 * 	},
	 * 	<virtual_inherit::BaseB> = {
	 * 		members of virtual_inherit::BaseB:
	 * 		_vptr$BaseB = 0x10007dc90 <vtable for virtual_inherit::Derived+72>,
	 * 		b = 30
	 * 	},
	 * 	<virtual_inherit::BaseC> = {
	 * 		_vptr$BaseC = 0x10007dcb8 <vtable for virtual_inherit::Derived+112>,
	 * 		c = 40
	 * 	},
	 * 	members of virtual_inherit::Derived:
	 * 	d = 50
	 * }
	 */
	using namespace virtual_inherit;
	auto derived = new Derived();
	auto addr = reinterpret_cast<uintptr_t *>(derived);

	// -----------------------------BaseA--------------------------------
	auto vptr = *reinterpret_cast<uintptr_t **>(addr);
	auto vbaseOffset = static_cast<ptrdiff_t>(vptr[-3]);
	std::cout << "vbaseOffset: " << vbaseOffset << std::endl;
	auto offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	BaseA *pBaseA = derived;
	auto offset = reinterpret_cast<uintptr_t>(pBaseA) - reinterpret_cast<uintptr_t>(derived);
	EXPECT_EQ(offsetToTop, -offset);

	auto typeInfoName = reinterpret_cast<std::type_info *>(vptr[-1])->name();
	EXPECT_STREQ(typeInfoName, typeid(*derived).name());

	auto fooValue = reinterpret_cast<long (*)(Derived *)>(vptr[2])(derived);
	EXPECT_EQ(fooValue, derived->d);

	auto barValue = reinterpret_cast<long (*)(Derived *)>(vptr[3])(derived);
	EXPECT_EQ(barValue, derived->d);

	auto *a = reinterpret_cast<uintptr_t *>(derived) + 1;
	EXPECT_EQ(*reinterpret_cast<long *>(a), derived->a);

	// ------------------------------BaseB--------------------------------
	vptr = *reinterpret_cast<uintptr_t **>(addr + 2);
	offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	BaseB *pBaseB = derived;
	offset = reinterpret_cast<uintptr_t>(pBaseB) - reinterpret_cast<uintptr_t>(derived);
	EXPECT_EQ(offsetToTop, -offset);

	typeInfoName = reinterpret_cast<std::type_info *>(vptr[-1])->name();
	EXPECT_STREQ(typeInfoName, typeid(*derived).name());

	fooValue = reinterpret_cast<long (*)(BaseB *)>(vptr[2])(pBaseB);
	EXPECT_EQ(fooValue, derived->d);

	auto *b = reinterpret_cast<uintptr_t *>(derived) + 3;
	EXPECT_EQ(*reinterpret_cast<long *>(b), derived->b);

	// ------------------------------BaseC--------------------------------
	vptr = *reinterpret_cast<uintptr_t **>(addr + 4);
	offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	BaseC *pBaseC = derived;
	offset = reinterpret_cast<uintptr_t>(pBaseC) - reinterpret_cast<uintptr_t>(derived);
	EXPECT_EQ(offsetToTop, -offset);

	typeInfoName = reinterpret_cast<std::type_info *>(vptr[-1])->name();
	EXPECT_STREQ(typeInfoName, typeid(*derived).name());

	fooValue = reinterpret_cast<long (*)(BaseC *)>(vptr[2])(pBaseC);
	EXPECT_EQ(fooValue, derived->d);

	barValue = reinterpret_cast<long (*)(BaseC *)>(vptr[3])(pBaseC);
	EXPECT_EQ(barValue, derived->d);

	auto *c = reinterpret_cast<uintptr_t *>(derived) + 5;
	EXPECT_EQ(*reinterpret_cast<long *>(c), derived->c);

	// ------------------------------Derived--------------------------------
	auto *d = reinterpret_cast<uintptr_t *>(derived) + 6;
	EXPECT_EQ(*reinterpret_cast<long *>(d), derived->d);

	// ------------------------------Base--------------------------------
	vptr = *reinterpret_cast<uintptr_t **>(addr + 7);
	offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	Base *pBase = derived;
	offset = reinterpret_cast<uintptr_t>(pBase) - reinterpret_cast<uintptr_t>(derived);
	EXPECT_EQ(offsetToTop, -offset);

	fooValue = reinterpret_cast<long (*)(Base *)>(vptr[2])(pBase);
	EXPECT_EQ(fooValue, derived->d);

	auto *s = reinterpret_cast<uintptr_t *>(derived) + 8;
	EXPECT_EQ(*reinterpret_cast<long *>(s), derived->s);

	std::cout << "derived->s " << derived->s << std::endl;
	std::cout << "derived->BaseA::s " << derived->BaseA::s << std::endl;
	std::cout << "derived->BaseB::s " << derived->BaseB::s << std::endl;

	auto as = reinterpret_cast<uintptr_t>(&derived->BaseA::s);
	auto bs = reinterpret_cast<uintptr_t>(&derived->BaseB::s);
	EXPECT_EQ(as, bs);
	EXPECT_EQ(as, reinterpret_cast<uintptr_t>(&derived->s));

	delete derived;
}

TEST(PolymorphismTest, FunctionOverloading) {
	using namespace function_overloading;
	const auto *pb = new Base();

	EXPECT_EQ(pb->foo(1), "Base::foo(long)");
	EXPECT_EQ(pb->foo(1, 2), "Base::foo(long, long)");

	delete pb;
}

TEST(PolymorphismTest, FunctionHiding) {
	using namespace function_hiding;
	const Base *pb = new Base();
	Base *pd = new Derived();

	EXPECT_STREQ(pd->foo(0), "Base::foo(long)");
	// error: expected single argument 'a', have 2 arguments
	// pd->foo(0, 0);
	EXPECT_STREQ(dynamic_cast<Derived *>(pd)->foo(0, 0), "Derived::foo(long, long)");

	EXPECT_STREQ(pb->bar(), "Base::bar()");
	EXPECT_STREQ(pd->bar(), "Base::bar()");
	EXPECT_STREQ(dynamic_cast<Derived *>(pd)->bar(), "Derived::bar()");

	delete pb;
	delete pd;
}
