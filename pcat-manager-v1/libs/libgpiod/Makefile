#
# Copyright (C) 2018-2019 Michael Heimpold <mhei@heimpold.de>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libgpiod
PKG_VERSION:=2.1.3
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@KERNEL/software/libs/libgpiod/
PKG_HASH:=2be4c0b03e995d236c0e476e14aeb475d7b431dd1439609b6d65c540f91eaf58

PKG_MAINTAINER:=Michael Heimpold <mhei@heimpold.de>
PKG_LICENSE:=LGPL-2.1-or-later
PKG_LICENSE_FILES:=COPYING

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

ifneq ($(CONFIG_PACKAGE_libgpiodcxx),)
CONFIGURE_ARGS += --enable-bindings-cxx
else
CONFIGURE_ARGS += --disable-bindings-cxx
endif

ifneq ($(CONFIG_PACKAGE_gpiod-tools),)
CONFIGURE_ARGS += --enable-tools
endif

TARGET_CPPFLAGS += -I$(PKG_BUILD_DIR)/include
TARGET_LDFLAGS += -L$(PKG_BUILD_DIR)/lib/.libs

define Package/libgpiod
  SECTION:=libs
  CATEGORY:=Libraries
  URL:=https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git
  TITLE:=Library for interacting with Linux's GPIO character device
  KCONFIG:= \
    CONFIG_GPIO_CDEV=y
  DEPENDS:=@GPIO_SUPPORT
endef

define Package/libgpiod/description
  C library for interacting with the linux GPIO character device
  (gpiod stands for GPIO device).
endef

define Package/gpiod-tools
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Tools for interacting with GPIO pins
  DEPENDS:=+libgpiod
endef

define Package/gpiod-tools/description
  Tools for interacting with the linux GPIO character device
  (gpiod stands for GPIO device).
endef

define Package/libgpiodcxx
  SECTION:=libs
  CATEGORY:=Libraries
  URL:=https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git
  TITLE:=C++ binding for libgpiod
  DEPENDS:=+libstdcpp +libgpiod
endef

define Package/libgpiodcxx/description
  This package contains the C++ binding for libgpiod.
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/gpiod.h $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libgpiod.{so*,a} $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libgpiod.pc $(1)/usr/lib/pkgconfig/

    ifneq ($(CONFIG_PACKAGE_libgpiodcxx),)
	$(CP) $(PKG_INSTALL_DIR)/usr/include/gpiodcxx $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/include/gpiod.hpp $(1)/usr/include/

	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libgpiodcxx.{so*,a} $(1)/usr/lib/

	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libgpiodcxx.pc $(1)/usr/lib/pkgconfig/
    endif
endef

define Package/libgpiod/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libgpiod.so.* $(1)/usr/lib/
endef

define Package/libgpiodcxx/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libgpiodcxx.so.* $(1)/usr/lib/
endef

define Package/gpiod-tools/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin/
endef

$(eval $(call BuildPackage,libgpiod))
$(eval $(call BuildPackage,libgpiodcxx))
$(eval $(call BuildPackage,gpiod-tools))
