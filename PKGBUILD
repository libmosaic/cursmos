# Maintainer: gilzoide <gilzoide@gmail.com>

pkgname=mosaic-git
pkgver=0.0.0
pkgrel=1
pkgdesc="A ASC art library"
arch=('i686' 'x86_64')
url="https://github.com/gilzoide/libmosaic"
license=("GPL")
depends=('pacman' 'ncurses')
makedepends=('git' 'scons')
source=("$pkgname"::'git://github.com/gilzoide/libmosaic.git')
md5sums=('SKIP')

# functions
pkgver () {
	cd "$pkgname"
	git log -n 1 --date=short | awk '/Date/ {gsub ("-",""); print $2}'
}

build () {
	cd "$pkgname"
	scons -j`nproc`
}

package () {
	scons install
}
