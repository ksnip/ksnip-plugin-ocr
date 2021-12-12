#!/bin/bash

echo "--> Create directory and copy everything we need to deliver"
mkdir ksnip-plugin-ocr-${VERSION_NUMBER}
cp -R CMakeLists.txt cmake/ LICENSE.txt README.md src/ ksnip-plugin-ocr-${VERSION_NUMBER}/
echo "--> Package source content"
tar -cvzf ksnip-plugin-ocr_${VERSION_NUMBER}.orig.tar.gz ksnip-plugin-ocr-${VERSION_NUMBER}/
echo "--> Copy source package to debian directory"
cp -R ${WORKSPACE}/.github/scripts/linux/deb/debian ksnip-plugin-ocr-${VERSION_NUMBER}/
