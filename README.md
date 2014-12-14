# xpath

tiny c utility for extracting data via xpath suitable for Hadoop streaming jobs

## usage

    $ ./xpath examples/simple.xml /doc/dest/@id '/doc/dest[@id="foo"]'
    foo	bar

    $ cat examples/simple.xml | ./xpath - //src/@ref
    foo

## install

update the libxml2 locations in the Makefile... this shouldn't be that complicated so I invested slightly more than 0 seconds into the build
