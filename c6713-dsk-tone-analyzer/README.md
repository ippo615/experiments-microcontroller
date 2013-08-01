C6713 DSK Tone Analyzer
=======================

This code is for C6713 DSK. It listens to the sounds on one of the inputs and
tries to determine which misic note is being played. It then transfers that 
information over a USB cable back to a Visual Basic program running on a
connected computer. It only works with pure sinusoidal notes and it only
reports the dominant note being played (ie if a chord is played it will not
report multiple notes).

The source code files (for both the board and the Visual Basic Program) can
be found in the `CCStudioFiles` folder. The `*.c` files are for the DSK and 
the `*.frm` files have the Visual Basic code. I divided the entire thing into
5 parts.

For a lot more info, read the Report.pdf.