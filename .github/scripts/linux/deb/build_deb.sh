#!/bin/bash

cd ksnip-plugin-ocr-${VERSION_NUMBER}

dpkg-buildpackage -us -uc -i -b

mv ${WORKSPACE}/ksnip-plugin-ocr_*.deb ${WORKSPACE}/ksnip-plugin-ocr-${VERSION}.deb
