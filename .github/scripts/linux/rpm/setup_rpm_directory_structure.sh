#!/bin/bash

echo "--> Create directory and everything we need to deliver"
mkdir ksnip-plugin-ocr-${VERSION_NUMBER}
cp -R CMakeLists.txt cmake/ LICENSE.txt README.md src/ ksnip-plugin-ocr-${VERSION_NUMBER}/

echo "--> Package directory"
tar -cvzf ksnip-plugin-ocr-${VERSION_NUMBER}.tar.gz ksnip-plugin-ocr-${VERSION_NUMBER}/

echo "--> Move package to SOURCE directory"
mkdir ksnip-plugin-ocr-${VERSION_NUMBER}/SOURCES
mv ksnip-plugin-ocr-${VERSION_NUMBER}.tar.gz ksnip-plugin-ocr-${VERSION_NUMBER}/SOURCES/

echo "--> Copy spec file to SPEC directory"
mkdir ksnip-plugin-ocr-${VERSION_NUMBER}/SPECS
cp ksnip-plugin-ocr.spec ksnip-plugin-ocr-${VERSION_NUMBER}/SPECS/ksnip-plugin-ocr-${VERSION_NUMBER}.spec
