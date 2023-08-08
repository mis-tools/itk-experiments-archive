set -e
#set -x
cwd=`pwd`

outputdir=$2

script_dir=$(dirname "$0")
source ${script_dir}/compile-static.sh "$@"
source ${script_dir}/compile-shared.sh "$@"

rm -rf $outputdir/debian/usr
mkdir -p $outputdir/debian/usr/bin
pyflakes python/*.py  # TODO: switch to flake8 when newer ubuntu version is used
cp python/*.py $outputdir/debian/usr/bin/
for f in $outputdir/static/bin/*; do
    dst=`echo $f | sed "s|$outputdir/static|$outputdir/debian/usr|"`
    cp $f "$dst-static"
done
for f in $outputdir/shared/bin/*; do
    dst=`echo $f | sed "s|$outputdir/shared|$outputdir/debian/usr|"`
    cp $f "$dst-shared"
done
cd $outputdir/debian/usr/bin
for f in *-static; do
    dst=`echo $f | sed 's/-static//'`
    ln -s $f $dst
done
cd $cwd
