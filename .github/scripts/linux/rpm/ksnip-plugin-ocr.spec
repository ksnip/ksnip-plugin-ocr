%define    packager           Damir Porobic <damir.porobic@gmx.com>
%define  __spec_install_post %{nil}
%define    debug_package     %{nil}
%define  __os_install_post   %{_dbpath}/brp-compress
%define  _signature           gpg
%define  _gpg_name            ksnip-plugin-ocr


Name:    ksnip-plugin-ocr
Summary: OCR plugin for ksnip
Version: X.X.X
Release: 1
Source0: %{name}-%{version}.tar.gz
URL:     https://github.com/ksnip/ksnip-plugin-ocr
License: GPLV2+
Group:   Application/Utility


%description
OCR plugin for ksnip

%prep
%setup

%build
cmake .
make

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%{_libdir}/lib%{name}*

%changelog
