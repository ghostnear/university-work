# Lab 2

Create two processes, a producer and a consumer, with the producer feeding the consumer.

Requirement: Compute the scalar product of two vectors.

Create two processes. The first process (producer) will compute the products of pairs of elements—one from each vector—and will feed the second process. The second process (consumer) will sum up the products computed by the first one. The two processes will be synchronized using inter-process communication mechanisms such as Pipe. The consumer will be able to use each product as soon as it is computed by the producer process.