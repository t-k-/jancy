#...............................................................................
#
#  This file is part of the Jancy toolkit.
#
#  Jancy is distributed under the MIT license.
#  For details see accompanying license.txt file,
#  the public copy of which is also available at:
#  http://tibbo.com/downloads/archive/jancy/license.txt
#
#...............................................................................

brew update
brew install coreutils
brew install lua
brew install ragel
brew install p7zip
brew install lcov

echo "axl_override_setting (GCC_FLAG_COVERAGE -coverage)" >> settings.cmake

# openssl is already installed, but not linked

echo "set (OPENSSL_INC_DIR /usr/local/opt/openssl/include)" >> paths.cmake
echo "set (OPENSSL_LIB_DIR /usr/local/opt/openssl/lib)" >> paths.cmake