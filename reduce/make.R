library(rmarkdown)

Sys.setenv(RSTUDIO_PANDOC="/usr/lib/rstudio/bin/pandoc")
render('reduce.Rmd')
browseURL('reduce.html')