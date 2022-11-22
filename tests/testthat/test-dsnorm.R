library("runjags")

mm <- "model{

  for(i in 1:10){
    x[i] ~ dsnorm(mean, sd, xi)
  }
  mean ~ dnorm(0,1)
  sd ~ dgamma(1,1)
  xi ~ dnorm(0,1)T(0,)

  #data# x
  #monitor# mean, sd, xi
}"

x <- rnorm(10)
run.jags(mm, method="rjags")


JAGSmodule:::rcpp_dsnorm(0.0, 0.171319, 0.805012, -0.890533, FALSE)
JAGSmodule:::dsnorm(0.0, -0.92253, 0.977969, -0.631178, FALSE)
JAGSmodule:::dsnorm(0.0, 0.0, 1.0, 0.0, FALSE)

test_that("multiplication works", {
  expect_equal(JAGSmodule:::rcpp_dsnorm(0.0, 0.0, 1.0, 0.0, FALSE), dnorm(0.0))
})
