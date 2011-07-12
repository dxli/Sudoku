htdir = /var/www/localhost/htdocs
HTTP_GROUP=$(shell [[ `id http 2>/dev/null` ]] && echo http || echo apache)

all:
	echo "Nothing to do"

clean: all

install:
	install -m755 -g ${HTTP_GROUP} -d ${htdir}; \
	install --backup=none -m644 -g ${HTTP_GROUP} -t ${htdir} sudoku.html



