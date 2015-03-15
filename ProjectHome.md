**RibTools** is a system composed of a few applications devoted to render Pixar's [RenderMan](http://en.wikipedia.org/wiki/RenderMan_Interface_Specification#RenderMan_compliant_renderers) RIB files and related high level [RenderMan Shading Language](http://en.wikipedia.org/wiki/RenderMan_Shading_Language) shaders (RSL).

The project is currently at a very early stage. Only simple files can be rendered and the support for high level shaders is very limited.

The purpose is to write a RenderMan compliant renderer, based on the [REYES](http://en.wikipedia.org/wiki/Reyes_rendering) architecture and optimized for speed. The code in RibRender is therefore built with many core technologies and vector processors in mind.

By default, executables are compiled to exploit the SSE2 instruction set.
As an experiment, the renderer also optionally supports 16-way vector SIMD utilizing the [C++ Larrabee Prototype Library](http://software.intel.com/en-us/articles/prototype-primitives-guide/) kindly released by Intel.

<p align='center'><b>Check out RibTool's <i>web site</i> over at <a href='http://ribtools.com'>http://ribtools.com</a></b></p>

## Sample images ##
Crude but real, in all their intrinsic beauty !

<img src='http://ribtools.googlecode.com/svn/trunk/Source/docs/images/sample_renders/airplane.png' width='50%'>

<img src='http://ribtools.googlecode.com/svn/trunk/Source/docs/images/sample_renders/killeroo.jpg' width='50%'>

<img src='http://ribtools.googlecode.com/svn/trunk/Source/docs/images/sample_renders/displaced_sphere.png' width='33%'>

<img src='http://ribtools.googlecode.com/svn/trunk/Source/docs/images/sample_renders/elephant.png' width='50%'>

<hr />
<i>RibTools and RibRender are: Copyright 2008-2010, Davide Pasca. All rights reserved.</i>

<i>The RenderMan (R) Interface Procedures and RIB Protocol are: Copyright 1988, 1989, Pixar. All rights reserved. RenderMan (R) is a registered trademark of Pixar.</i>