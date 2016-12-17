find c4.4xlarge -exec ./perf-parser.pl {} \; | \
  perl -nle 'print "c4.4xlarge, $_"' >> datafile
find c4.8xlarge -exec ./perf-parser.pl {} \; | \
  perl -nle 'print "c4.8xlarge, $_"' >> datafile
