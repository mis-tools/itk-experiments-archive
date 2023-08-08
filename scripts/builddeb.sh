#!/bin/bash
# postbuild script for debian package build.
# Must be called from the git base directory.

BUILD_NUMBER=$1

set -e
cwd=`pwd`

script_dir=$(dirname "$0")
cd ${script_dir}/..

outputdir=output
debdir=$outputdir/debian
rm -rf $debdir

# build using custom downloaded version of itk
source ${script_dir}/compile.sh ${script_dir}/build_itk.sh $outputdir

version="1.0.0"

package="itk-experiments-archive"
maintainer="https://github.com/mis-tools/itk-experiments-archive <https://github.com/mis-tools/itk-experiments-archive/issues>"
arch="amd64"
echo "package=$package"

echo "Compute md5 checksum."
cd $debdir
mkdir -p DEBIAN
find . -type f ! -regex '.*?debian-binary.*' ! -regex '.*?DEBIAN.*' -printf '%P ' | xargs md5sum > DEBIAN/md5sums
cd $cwd

#date=`date -u +%Y%m%d`
#echo "date=$date"

#gitrev=`git rev-parse HEAD | cut -b 1-8`
gitrevfull=`git rev-parse HEAD`
gitrevnum=`git log --oneline | wc -l | tr -d ' '`
#echo "gitrev=$gitrev"

buildtimestamp=`date -u +%Y%m%d-%H%M%S`
hostname=`hostname`
echo "build machine=${hostname}"
echo "build time=${buildtimestamp}"
echo "gitrevfull=$gitrevfull"
echo "gitrevnum=$gitrevnum"

debian_revision="${gitrevnum}"
upstream_version="${version}"
echo "upstream_version=$upstream_version"
echo "debian_revision=$debian_revision"

packageversion="${upstream_version}-git${debian_revision}"
packagename="${package}_${packageversion}_${arch}"
echo "packagename=$packagename"
packagefile="${packagename}.deb"
echo "packagefile=$packagefile"

description="build machine=${hostname}, build time=${buildtimestamp}, git revision=${gitrevfull}"
if [ ! -z ${BUILD_NUMBER} ]; then
    echo "build number=${BUILD_NUMBER}"
    description="$description, build number=${BUILD_NUMBER}"
fi

installedsize=`du -s $debdir/ | awk '{print $1}'`

#for format see: https://www.debian.org/doc/debian-policy/ch-controlfields.html
cat > $debdir/DEBIAN/control << EOF |
Section: science
Priority: extra
Maintainer: $maintainer
Version: $packageversion
Package: $package
Architecture: $arch
Installed-Size: $installedsize
Description: $description
Conflicts: brainreader-pipeline-binaries
Breaks: brainreader-pipeline-binaries
EOF

echo "Creating .deb file: $packagefile"
rm -f ${package}_*.deb
fakeroot dpkg-deb --build $debdir $packagefile

echo "Package info"
dpkg -I $packagefile
