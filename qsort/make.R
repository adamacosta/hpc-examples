library(rmarkdown)

Sys.setenv(RSTUDIO_PANDOC="/usr/lib/rstudio/bin/pandoc")
render('qsort.Rmd')
browseURL('qsort.html')