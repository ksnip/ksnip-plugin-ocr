#!/bin/bash

cd ksnip-plugin-ocr-${VERSION_NUMBER}

rpmbuild -ba SPECS/ksnip-plugin-ocr-*.spec --define '_topdir %(pwd)'

mv ${WORKSPACE}/ksnip-plugin-ocr-${VERSION_NUMBER}/RPMS/x86_64/ksnip-*.rpm ${WORKSPACE}/ksnip-plugin-ocr-${VERSION}.rpm
