#!/bin/bash

echo "--> Create copy of spec file"
cp ${WORKSPACE}/.github/scripts/linux/rpm/ksnip-plugin-ocr.spec .

echo "--> Update changelog entries"
cp CHANGELOG.md changelog
sed -i '1,2d' changelog  #Remove header and empty line ad the beginning
sed -i 's/* /-- /g' changelog # Replace asterisk with double dash
sed -i 's/\[\(.*[^]]*\)\].*/\1)/g' changelog # Replace links to issues with only number
sed -i "s/## Release \([0-9]*\.[0-9]*\.[0-9]*\)/* ${BUILD_DATE} Damir Porobic <damir.porobic@gmx.com> \1/" changelog # Format release headers
cat changelog >> ksnip-plugin-ocr.spec

echo "--> Update version"
sed -i "s/Version: X.X.X/Version: ${VERSION_NUMBER}/" ksnip-plugin-ocr.spec
sed -i "s;cmake .;cmake . -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_PREFIX_PATH=${INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DBUILD_TESTS=${BUILD_TESTS} -DBUILD_EXAMPLE=${BUILD_EXAMPLE};" ksnip-plugin-ocr.spec # ; is the delimiter
