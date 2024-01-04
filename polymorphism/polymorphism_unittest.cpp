//
// Created by yp on 2023/12/27.
//

#include <typeinfo>
#include <gtest/gtest.h>
#include "normal_inherit.h"
#include "virtual_inherit.h"

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

	// -----------------------------BaseA--------------------------------
	auto vptr = *reinterpret_cast<uintptr_t **>(derived);
	auto offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	std::cout << "BaseA offsetToTop: " << offsetToTop << std::endl;
	auto *pBaseA = dynamic_cast<BaseA *>(derived);
	auto offset = (uintptr_t)pBaseA - (uintptr_t)derived;
	EXPECT_EQ(offsetToTop, -offset);
	auto typeInfoName = reinterpret_cast<std::type_info *>(vptr[-1])->name();
	EXPECT_STREQ(typeInfoName, typeid(*derived).name());
	auto fooValue = reinterpret_cast<long (*)(Derived *)>(vptr[2])(derived);
	EXPECT_EQ(fooValue, derived->d);

	auto *s = reinterpret_cast<uintptr_t *>(derived) + 1;
	EXPECT_EQ(*reinterpret_cast<long *>(s), derived->BaseA::s);

	auto *a = reinterpret_cast<uintptr_t *>(derived) + 2;
	EXPECT_EQ(*reinterpret_cast<long *>(a), derived->a);

	// ------------------------------BaseB--------------------------------
	vptr = *reinterpret_cast<uintptr_t **>((uintptr_t *)derived + 3);
	offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	std::cout << "BaseB offsetToTop: " << offsetToTop << std::endl;
	auto *pBaseB = dynamic_cast<BaseB *>(derived);
	offset = (uintptr_t)pBaseB - (uintptr_t)derived;
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
	vptr = *reinterpret_cast<uintptr_t **>((uintptr_t *)derived + 6);
	offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	std::cout << "BaseC offsetToTop: " << offsetToTop << std::endl;
	auto *pBaseC = dynamic_cast<BaseC *>(derived);
	offset = (uintptr_t)pBaseC - (uintptr_t)derived;
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
	auto as = reinterpret_cast<uintptr_t>(&derived->BaseA::s);
	auto bs = reinterpret_cast<uintptr_t>(&derived->BaseB::s);
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

	// -----------------------------BaseA--------------------------------
	auto vptr = *reinterpret_cast<uintptr_t **>(derived);
	auto offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	auto *pBaseA = dynamic_cast<BaseA *>(derived);
	auto offset = (uintptr_t)pBaseA - (uintptr_t)derived;
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
	vptr = *reinterpret_cast<uintptr_t **>((uintptr_t *)derived + 2);
	offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	auto *pBaseB = dynamic_cast<BaseB *>(derived);
	offset = (uintptr_t)pBaseB - (uintptr_t)derived;
	EXPECT_EQ(offsetToTop, -offset);

	typeInfoName = reinterpret_cast<std::type_info *>(vptr[-1])->name();
	EXPECT_STREQ(typeInfoName, typeid(*derived).name());

	fooValue = reinterpret_cast<long (*)(BaseB *)>(vptr[2])(pBaseB);
	EXPECT_EQ(fooValue, derived->d);

	auto *b = reinterpret_cast<uintptr_t *>(derived) + 3;
	EXPECT_EQ(*reinterpret_cast<long *>(b), derived->b);

	// ------------------------------BaseC--------------------------------
	vptr = *reinterpret_cast<uintptr_t **>((uintptr_t *)derived + 4);
	offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	auto *pBaseC = dynamic_cast<BaseC *>(derived);
	offset = (uintptr_t)pBaseC - (uintptr_t)derived;
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
	vptr =  *reinterpret_cast<uintptr_t **>((uintptr_t *)derived + 7);
	offsetToTop = static_cast<ptrdiff_t>(vptr[-2]);
	auto *pBase = dynamic_cast<Base *>(derived);
	offset = (uintptr_t)pBase - (uintptr_t)derived;
	EXPECT_EQ(offsetToTop, -offset);

	fooValue = reinterpret_cast<long (*)(Base *)>(vptr[2])(pBase);
	EXPECT_EQ(fooValue, derived->d);

	auto *s = reinterpret_cast<uintptr_t *>(derived) + 8;
	EXPECT_EQ(*reinterpret_cast<long *>(s), derived->s);

	auto as = reinterpret_cast<uintptr_t>(&derived->BaseA::s);
	auto bs = reinterpret_cast<uintptr_t>(&derived->BaseB::s);
	EXPECT_EQ(as, bs);

	delete derived;
}
