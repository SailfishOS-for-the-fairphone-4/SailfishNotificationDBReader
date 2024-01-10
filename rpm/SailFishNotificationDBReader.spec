Name: sailfish-notification-db-reader

Summary: Utility program that reads the notification database
Version: 1.0.1
Release: 1
License: Custom
URL: https://github.com/SailfishOS-for-the-fairphone-4/SailfishNotificationDBReader
Source: ${name}-%{version}.tar.bz2
Requires: sqlite
Requires: sqlite-libs
BuildRequires: sqlite-devel

%description
Utility program that reads the notification database

%prep
%setup -q -n %{name}-%{version}

%build

%cmake .
%make_build %{?_smp_mflags}

%install
%make_install DESTDIR=%{buildroot}

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
/usr/bin/SailFishNotificationDBReader
