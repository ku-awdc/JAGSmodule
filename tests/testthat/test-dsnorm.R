library("runjags")

mm <- "model{

  x ~ dsnorm(mean, sd, xi)
  mean ~ dnorm(0,1)
  sd ~ dgamma(1,1)
  xi ~ dnorm(0,1)T(0,)

  #data# x
  #monitor# mean, sd, xi
}"

x <- 0
run.jags(mm, method="rjags")


JAGSmodule:::rcpp_dsnorm(0.0, 0.171319, 0.805012, -0.890533, FALSE)
JAGSmodule:::dsnorm(0.0, -0.92253, 0.977969, -0.631178, FALSE)
JAGSmodule:::dsnorm(0.0, 0.0, 1.0, 0.0, FALSE)

test_that("multiplication works", {
  expect_equal(2 * 2, 4)
})
