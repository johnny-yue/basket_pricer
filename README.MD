# basket pricer

Basket price update can be done via "delta * weight" of a constinuat, thus does not requrie the computation of all constituents' price each update.

Provide a IDataSource for dependcy injection.

Load configuation outside of business logic class to seperate the responsibility of classes.

## Compile / Run

mkdir bld

cd bld

cmake ..

make
