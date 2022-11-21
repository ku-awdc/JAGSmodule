.onLoad <- function(lib, pkg)
{
    ## Load the dynlib
    library.dynam("JAGSmodule", pkg, lib, local=FALSE)

    ## Load the JAGS module
    modloc <- gsub('/$','', file.path(lib, pkg, 'libs', .Platform$r_arch))
    rjags::load.module("JAGSmodule", modloc, quiet=TRUE)

    ## And the Rcpp module
    Rcpp::loadModule("jags_module", TRUE)
}

.onAttach <- function(lib, pkg)
{
    packageStartupMessage("Loaded modules: ",
                          paste(rjags::list.modules(), collapse=","))
}

.onUnload <- function(libpath)
{
    rjags::unload.module("JAGSmodule", quiet=TRUE)
    library.dynam.unload("JAGSmodule", libpath)
}

