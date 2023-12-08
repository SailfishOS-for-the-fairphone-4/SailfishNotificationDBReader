Name: sailfish-notification-db-reader

Summary: Utility program that reads the notification database
Version: 1.0.0
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
mkdir build

%build
cd build

%cmake ..
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
cd build
cmake --install .

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig