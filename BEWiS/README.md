# BEWiS
Background Estimation by Weightless Neural Networks

> Authors: Maurizio Giordano and Massimo De Gregorio
> - Istituto di Calcolo e Reti ad Alte Prestazioni (ICAR) - Consiglio Nazionale delle Ricerche (CNR) (Italy)
> - Istituto di Scienze Applicate e Sistemi Intelligenti "Eduardo Caianiello" (ISASI) - Consiglio Nazionale delle Ricerche (CNR) (Italy)

----------------------
Description
----------------------

BEWiS is a background modeling approach for videos based on a weightless neural system, 
namely WiSARD<sup>rp</sup>, with the aim of exploiting its features of being highly adaptive and 
noise–tolerance at runtime.
In BEWiS, the changing pixel colors in a video are processed by an incremental 
learning neural network with a limited-in-time memory-retention mechanism that allow the
proposed system to absorb small variations of the learned model (background) 
in the steady state of operation as well as to  fastly adapt to background 
changes during the video timeline.

----------------------
Citation Details
----------------------
  
This work is the subject of the article:

M. De Gregorio, M. Giordano.
 "Background Estimation by Weightless Neural Networks".
 Submitted to "Pattern Recognition Letters - Special Issue on Scene Background Modeling and Initialization".
 
At the current time, when using this source code please reference this work by citing the following
paper which deals with a previous version of this software:

 M. De Gregorio, M. Giordano.
 Background Modeling by Weightless Neural Networks.
 In "New Trends in Image Analysis and Processing - ICIAP 2015 Workshops", 
 Volume 9281 of the series Lecture Notes in Computer Science, pp 493-501.
 Springer Verlag, http://dx.doi.org/10.1007/978-3-319-23222-5_60 
 
Bibtex:

```
@Inbook{DeGregorio2015,
    author="De Gregorio, Massimo and Giordano, Maurizio",
    editor="Murino, Vittorio and Puppo, Enrico and Sona, Diego and Cristani, Marco and Sansone, Carlo"
    title="Background Modeling by Weightless Neural Networks",
    bookTitle="New Trends in Image Analysis and Processing -- ICIAP 2015 Workshops: ICIAP 2015 International Workshops, BioFor, CTMR, RHEUMA, ISCA, MADiMa, SBMI, and QoEM, Genoa, Italy, September 7-8, 2015, Proceedings",
    year="2015",
    publisher="Springer International Publishing",
    address="Cham",
    pages="493--501",
    isbn="978-3-319-23222-5",
    doi="10.1007/978-3-319-23222-5_60",
    url="http://dx.doi.org/10.1007/978-3-319-23222-5_60"
}
```

----------------------
License
----------------------
  
The source code is provided without any warranty of fitness for any purpose.
You can redistribute it and/or modify it under the terms of the
GNU General Public License (GPL) as published by the Free Software Foundation,
either version 3 of the License or (at your option) any later version.
A copy of the GPL license is provided in the "GPL.txt" file.

----------------------
Compile/Run BEWiS source (Linux, Mac OSX)
----------------------

To run the code the following libraries are required:

1. OpenCV 3.0 (later versions may also work)

2. CMake  3.0  (later version may also work)

3. C++ Compiler (tested only with GCC 5.x or later versions)

```
$ cmake .
$ make
$ bewis  -i <video-filepathname>
```

----------------------
Create Docker Container to test BEWiS (Any system)
----------------------

Require docker 1.12.x or later (avauilable at: https://docs.docker.com)

```
$ docker build -t bewis/pyopencv:latest .
root@\<imagetag\>:/home/BEWiS# docker run -i -t bewis/pyopencv:latest /bin/bash
root@\<imagetag\>:/home/BEWiS# ./bewis  -i foliage.avi
```


