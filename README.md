
</head>
<body>
<div id="header">
<h1 class="title">103 Project 8: Mandelbrot Set</h1>
</div>

<!---{{ Synopsis-->
<h2 id="synopsis">Synopsis</h2>
<p>In this project, you will implement a simple program to plot the famous <a href="http://en.wikipedia.org/wiki/Mandelbrot_set">Mandelbrot set</a>. It doesn’t have much mathematical significance that I know of, but it does make pretty pictures. It also makes for good programming practice.</p>
<p>Here are a few things you’ll get out of this project:</p>
<ul>
<li>A very brief introduction to GUI programming;</li>
<li>More about classes and a very brief introduction to object oriented programming;</li>
<li>Refinement of your overall coding skill.</li>
<li>Fun (???)</li>
</ul>
<div class="figure">
<img src="fig1.jpeg" alt="Fig. 1: Mandelbrot Set, as rendered by project 8’s code" />
<p class="caption">Fig. 1: Mandelbrot Set, as rendered by project 8’s code</p>
</div>
<h3 id="suggested-reading">Suggested Reading</h3>
<ul>
<li>Chapters 12 – 14 of the book cover graphics programming. You should read these chapters. Some of the specifics will not apply since we are using a different library, but there’s tons of general, useful information in there.</li>
<li>If you’re still not feeling all that comfortable with classes, you may want to review chapter 9 of the book, as well as <a href="http://www.charlesli.org/pic10a/lectures/lecture17/index.html">Charles Li’s notes on structures</a>.</li>
</ul>
<h3 id="important-notes-on-grading">Important Notes on Grading</h3>
<p>This project is to be done collaboratively. Teams <strong>must be 3 – 4 people</strong>, and <strong>your teammates must be in the same recitation</strong>. Details:</p>
<ul>
<li>Everyone should be signed up on [bitbucket][bitbucket].</li>
<li>Designate one member of your team to be the leader / repository owner. (They’ll set up the repository and grant access to the rest of the team.)</li>
<li>Commits from the team members can be incorporated in one of two ways:
<ol style="list-style-type: decimal">
<li>Follow the instructions on [collaborating with git][scm]. (Team leaders: don’t forget to give other members write access to the repository.)</li>
<li>Use [bitbucket’s fork + pull request][pullreq] features.</li>
</ol>
<strong>NOTE:</strong> Either way you do it, you should follow the guidelines given above about [avoiding merge conflicts][scm].</li>
<li>Team leaders – please <em>edit</em> (or start, if it doesn’t exist) a piazza post containing the url of your repository, and a list of the team’s members. Please make different posts for each section (MM,MM2,MM3).</li>
<li>Your projects will be graded based on whether or not they pass the automated tests, and whether or not each team member is contributing (as evidenced by the commit logs).</li>
</ul>
<!---}}-->
<!---{{ intro-->
<h2 id="introduction">Introduction</h2>
<p>For the history, I direct you to the <a href="http://en.wikipedia.org/wiki/Mandelbrot_set">wikipedia page</a>. However, there is one little tidbit that I thought was entertaining, and which ought to make you grateful you weren’t trying to program computers in the 70’s – the original picture of the Mandelbrot set looked something like this:</p>
<div class="figure">
<img src="Mandel.png" alt="Fig. 2: First image of Mandelbrot set" />
<p class="caption">Fig. 2: First image of Mandelbrot set</p>
</div>
<p>As you have seen before, the Mandelbrot set (which we’ll denote by <span class="math inline"><em>M</em></span>) is defined as the set of points in the complex plane for which a certain iterated sequence does not diverge. More precisely, for a complex number <span class="math inline"><em>c</em></span>, we define a sequence <span class="math inline">{<em>c</em><sub><em>n</em></sub>}</span> by <span class="math inline"><em>c</em><sub>0</sub> = 0</span>, and for all other <span class="math inline"><em>n</em></span>, <span class="math inline"><em>c</em><sub><em>n</em></sub> = <em>c</em><sub><em>n</em> − 1</sub><sup>2</sup> + <em>c</em></span>. We then define <span class="math inline"><em>M</em></span> as the set of complex numbers for which this sequence does not diverge.<a href="#fn1" class="footnoteRef" id="fnref1"><sup>1</sup></a></p>
<p><em>Note:</em> if <span class="math inline">|<em>c</em><sub><em>n</em></sub>|&gt;2</span> for any <span class="math inline"><em>n</em></span>, then the sequence must diverge. (Exercise: prove this statement.) But for smaller numbers, it is not so easy to see what happens. What we’ll end up doing is just gathering empirical evidence, and make a judgment based on that. That is, we will iterate the sequence over and over, and if we never see a value with norm bigger than 2, we’ll assume it is in the set. And if it is not in the set, the number of iterations required to get the norm greater than 2 will give us some indication of <em>how close it is</em> to <span class="math inline"><em>M</em></span>. We can use that information to pick the colors.</p>
<!---}}-->
<!---{{ Details-->
<h2 id="details">Details</h2>
<h3 id="graphical-user-interfaces">Graphical User Interfaces</h3>
<p>At last, we are writing a program that a non-computer-nerd could actually use! (Although it is probably only computer nerds that would <em>want</em> to use it…) That’s right folks, our program has menus, stuff happens when you can click on it, and it even makes pretty pictures. But unfortunately, writing a GUI in C++ is not a trivial task. Writing it from the ground up would be way out of scope, highly platform-dependent, and is probably not something you’ll ever end up doing. Thus, we will make use of an established library for this sort of thing. In particular, we’ll use the <a href="http://en.wikipedia.org/wiki/Qt_%28framework%29">Qt library</a>. You can get a lot of the documentation at <a href="http://qt-project.org/">their website</a>, and there are also some nice tutorials available <a href="http://doc.trolltech.com/4.3/tutorial-t1.html">here</a>. Qt works across most major platforms (Linux, Windows, Mac), and is used by a lot of different applications.</p>
<p>The Qt library is large and complex; I will try to explain here the parts you need to know so that you don’t have to sift through the mounds of documentation on your own.</p>
<p><em>Note:</em> unlike our past projects, you will have to take a little more of this one on faith. It is not reasonable to ask you to understand the Qt library in much detail right now. I just want you to get a feel for GUI programming – don’t worry if you don’t catch everything that is going on. And if you do catch everything that’s going on …then you’re probably kidding yourself.</p>
<h3 id="overview-of-the-files">Overview of the files</h3>
<p>Let’s take a brief look through the project files, and get you oriented and ready to work.</p>
<h4 id="complex.hcpp"><code>complex.{h,cpp}</code></h4>
<p>These are of course the files for your complex number class. They provide overloaded operators for arithmetic, so that you can use natural expressions with them in your C++ code, like <code>z = w*y + c</code>. Some of the functions are left for you to write. This part of the project is not hard, but should be good practice.</p>
<h4 id="mainwindow.hcpp"><code>mainwindow.{h,cpp}</code></h4>
<p>Here we define the class for the main window of the application. It contains some boilerplate stuff like setting up the menus, and connecting functions to different user interface actions. You shouldn’t need to modify them. See the section below on <em>signals and slots</em> for a little more detail.</p>
<h4 id="mset.hcpp"><code>mset.{h,cpp}</code></h4>
<p>These files define and implement a class called <code>mandelbrotArea</code>, which will be responsible for drawing the images of the Mandelbrot set. The declaration of the class looks like this:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> mandelbrotArea : <span class="kw">public</span> <span class="ot">QWidget</span></code></pre></div>
<p>As you can see, our class <em>inherits</em> from the <code>QWidget</code> class. Remember what we talked about in lecture: this means that every instance of <code>mandelbrotArea</code> <strong>is an instance</strong> of <code>QWidget</code> as well. So, we get all the <code>QWidget</code> functions for free, and we can also redefine them when it is convenient. Documentation for the <code>QWidget</code> class can be found <a href="http://qt-project.org/doc/qt-4.8/QWidget.html">here</a>, but I would not recommend reading the whole thing. I would instead recommend you just jump to the <a href="http://qt-project.org/doc/qt-4.8/QWidget.html#events">part about events</a>. The gist of it is, by writing our own versions of these functions, we can control how our application responds to various user inputs. For example, if we want to have our program respond to the user double-clicking on our window, we can implement the following function:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> mouseDoubleClickEvent(<span class="ot">QMouseEvent</span> *event);</code></pre></div>
<p>The function gives us a pointer to a <code>QMouseEvent</code>, which contains useful information, like the <span class="math inline"><em>x</em>, <em>y</em></span> coordinates of where the double-click happened. You can get the details <a href="http://qt-project.org/doc/qt-4.8/qmouseevent.html">here</a>.</p>
<h4 id="signals-and-slots">Signals and Slots</h4>
<p>I would be remiss if I did not mention the <a href="http://qt-project.org/doc/qt-5.0/signalsandslots.html">signals and slots mechanism of Qt</a>. You don’t have to worry about it for most of the pieces of the project for which you’re responsible, but this is the general mechanism by which Qt objects talk to each other, so you should at least have heard of it! The super-high-level summary is this: if you want a member function in one of your QWidget-derived classes to respond to an event (a.k.a. a “signal”), declare your member function in the <code>slots</code> section, and connect it to the right signal with the <code>connect(...)</code> function. You can create your own signals, but often the predefined ones suffice. Let’s take a quick look at an example from the <code>MainWindow</code> class. We wanted <code>refreshImage()</code> to be called upon the user clicking a menu item.</p>
<p>Step 1: declare <code>refreshImage</code> under the slots of <code>mandelbrotArea</code>:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">public</span> <span class="kw">slots</span>:
    <span class="dt">void</span> refreshImage();</code></pre></div>
<p>Step 2: create an action in the main window, and connect it to the <code>refreshImage</code> slot of our instance (<code>msetArea</code>) of type <code>mandelbrotArea</code>:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">refreshAct = <span class="kw">new</span> <span class="ot">QAction</span>(<span class="fu">tr</span>(<span class="st">&quot;&amp;Redraw image&quot;</span>), <span class="kw">this</span>);
<span class="fu">connect</span>(refreshAct, <span class="kw">SIGNAL</span>(triggered()), msetArea, <span class="kw">SLOT</span>(refreshImage()));</code></pre></div>
<p>Step 3: create a menu entry for the action:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">optionMenu = <span class="kw">new</span> <span class="ot">QMenu</span>(<span class="fu">tr</span>(<span class="st">&quot;&amp;Options&quot;</span>), <span class="kw">this</span>);
optionMenu-&gt;addAction(refreshAct);</code></pre></div>
<p>That’s it. Should you find yourself with an abundance of time and interest, check out the link above to learn more.</p>
<h3 id="what-youre-supposed-to-do">What you’re supposed to do</h3>
<p>Your job is to do the following:</p>
<ol style="list-style-type: decimal">
<li>Finish off the implementation of the complex number class.</li>
<li>Write a function that draws the Mandelbrot set into a <code>QImage</code>, and displays it in the main window.</li>
<li>Implement a “zoom” feature. When the user double-clicks on the window (with the left mouse button), re-center the window at those coordinates, and zoom in by a factor of two (so the region of the complex plane we are viewing is half as wide and half as high as before). If the user double clicks with the right mouse button, zoom back out, again with the window centered at the coordinates of the mouse click.</li>
</ol>
<h3 id="testing">Testing</h3>
<p>Since there is no command line interface, the easiest way to test is to just run your program and mess around with it yourself. Make sure it is drawing something that looks like the Mandelbrot set. As always, it is a good idea to compile often and commit often. If you program too much without a compile, you may find yourself lost in an ocean of broken code, and you won’t even know which direction to the shore. I think some of you may have learned this the hard way during the last project…</p>
<!---}}-->
<!---{{ Building-->
<h2 id="building-the-project">Building the Project</h2>
<h3 id="the-steps">The steps</h3>
<ol style="list-style-type: decimal">
<li>From the project’s directory, run <code>qmake-qt4 -o Makefile mset.pro</code></li>
<li>Run <code>make</code> as usual.</li>
</ol>
<p><strong>You only have to do step 1 once.</strong> Subsequent builds are performed just by running <code>make</code>.</p>
<h3 id="the-explanation">The explanation</h3>
<p>Qt uses a <em>makefile generator</em> which, as the name suggests, makes makefiles. The makefile it generates will have all the right linker options so that you can use the Qt library, but it will also do less expected things like <em>generating source files</em>. The generated source files start with the prefix <code>moc_</code>, which stands for “meta-object compiler”. If you want to read more about it, you can see the documentation <a href="http://qt-project.org/doc/qt-4.8/metaobjects.html">here</a>, but I would probably not recommend it. Just be happy that it works. Like I said, there are going to be some details hidden from you this time, which I believe is unavoidable given our time constraints. Anyway, don’t be alarmed by the new source files that appear in your directory. I have already added them to the <code>.gitignore</code> file, so they should not clutter your repository’s status.</p>
<!---}}-->
<!---{{ Hints-->
<h2 id="other-hints-and-notes">Other Hints and Notes</h2>
<h3 id="debugging">Debugging</h3>
<p>At times, you will probably want to do some debugging. And if not outright debugging, perhaps you would just like to check on the contents of some of your variables. The easiest way is to just <code>cout</code> them. If you run your program from a terminal, then <code>cout</code> will be attached to it, so you’ll see the messages show up there. If you really want to stay away from anything console related, you can use the <a href="http://qt-project.org/doc/qt-4.8/qmessagebox.html">message box function</a>.</p>
<h3 id="screen-coordinates-and-affine-transformations">Screen coordinates and affine transformations</h3>
<p>In several instances, you’ll need to map one set of coordinates (for example, screen coordinates) into another set of coordinates (like the complex plane). This is pretty straightforward, but perhaps some additional explanation would be of use. First, note that screen coordinates are a little strange, in that they are anchored in the upper left corner (that is, the point <span class="math inline">(0, 0)</span> corresponds to the top left corner of the window). It looks something like the following diagram:</p>
<div class="figure">
<img src="coords.jpg" alt="Fig. 2: Regular coordinates vs. screen coordinates." />
<p class="caption">Fig. 2: Regular coordinates vs. screen coordinates.</p>
</div>
<p>Now you will want to not only convert the screen coordinates into more normal coordinates, but furthermore, you will want to do so with a <em>scaling factor</em>, as well as a <em>translation</em>. If you’ve had linear algebra class, then this will make perfect sense, and requires no explanation. If not, then read on…</p>
<p>To figure out an explicit formula for this mapping, we’ll use something akin to the “point-slope” formula you learned way back in middle school. In our special case of scaling + translation with screen coordinates to math coordinates, the formula is pretty simple – something like <span class="math inline">(<em>x</em>, <em>y</em>)↦(<em>s</em><em>x</em> + <em>a</em>, −<em>s</em><em>y</em> + <em>b</em>)</span>, where <span class="math inline"><em>s</em></span> is the scaling factor, and the pair <span class="math inline">(<em>a</em>, <em>b</em>)</span> is the translation vector.<a href="#fn2" class="footnoteRef" id="fnref2"><sup>2</sup></a> Notice that to solve for <span class="math inline">(<em>a</em>, <em>b</em>)</span>, all we need to do is plug in <span class="math inline">(0, 0)</span> and see where we want it to go. To figure out <span class="math inline"><em>s</em></span>, you just have to take the ratio of the width of the screen in both coordinate systems. Easy, right? Here’s a quick example, in case you’re still a little unclear.</p>
<p>Suppose your screen is <span class="math inline">500</span> by <span class="math inline">500</span> pixels, and you want to map that to the rectangle in the complex plane with <span class="math inline">( − 2, ±1.5)</span> and <span class="math inline">(1, ±1.5)</span> as the corners. Then <span class="math inline">(0, 0)</span> would map to <span class="math inline">( − 2, 1.5)</span>, and <span class="math inline">500</span> pixels in the screen must fit into <span class="math inline">3</span> units of the complex plane. So, the formula is then <span class="math inline">(<em>x</em>, <em>y</em>)↦((3/500)<em>x</em> − 2, −(3/500)<em>y</em> + 1.5)</span>.</p>
<p>Oh – one last thing. For some reason, I chose to set the variable <code>llCoord</code> to be the <em>lower</em> left point of the viewable region of the complex plane, instead of the <em>upper</em> left, so you will want to add the point <span class="math inline">(0, <em>h</em>)</span> to the formula, where <span class="math inline"><em>h</em></span> is the height of the window (in complex plane units). Or you could just change the meaning, and set <code>llCoord</code> to the upper left coordinate in the constructor, and then maintain that throughout.</p>
<h3 id="tuning-the-picture">Tuning the picture</h3>
<p>To get a nicer picture, you may want to automatically increase the number of iterations as the zoom level increases. For small numbers of zooms, you can probably just add 50 or 100 each time and it will look decent. Experiment to get it the way you want. For large numbers of zooms, you might want to do something non-linear. Also, for high levels of zoom, you might want to make a steeper color gradient, since there is a tighter range (as a ratio with the maximum number of iterations) that everything is crammed into.</p>
<h3 id="tuning-the-performance">Tuning the performance</h3>
<p>The complex number class gave a nice way to express our program. It enabled us to write natural-looking code with the basic arithmetic operators. However, this is not the best thing for performance, as it turns out. Take a look at a statement like this:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">complex z,w,r;
r = z*z + w;</code></pre></div>
<p>The compiler has to invent temporary variables of type <code>complex</code> to store the intermediate results of the squaring and the addition, and then copy those results into <code>r</code>. This all happens incredibly fast, so if you are only doing a few, you’d never need to improve it. But in our situation, something like the above happens inside a loop, which is inside a loop, which is inside a loop. It happens <strong>tons</strong> of times for each rendering. So if you can make that little piece go 30% faster, you’ll probably notice the difference in your program. How to make it go faster? The easiest way is to rewrite the statements without the operators. Just directly code the formulas for the real and imaginary parts of the result. Try it out!</p>
<p>By the way, if you just want to draw the pictures a little faster while you’re testing, the easiest thing to do is make the window smaller. You can take care of that in the <code>MainWindow</code> constructor.</p>
<!---}}-->
<!---{{ Feeling bored?-->
<h2 id="feeling-bored">Feeling Bored?</h2>
<p>If you have the project done ahead of time, there are tons of ways you can make improvements. Here’s a quick list of things that come to mind, approximately in ascending order of difficulty. (<em>Note:</em> the last few are <strong>hard</strong>.)</p>
<ol style="list-style-type: decimal">
<li>Add a control for the maximum number of iterations.</li>
<li>Mess with different color schemes.</li>
<li>Make adjustments if the window is resized. Make sure you don’t alter the scaling (don’t stretch the image, just show more or less of it). And now for the <strong>hard ones:</strong></li>
<li>Try to implement <a href="http://en.wikipedia.org/wiki/Mandelbrot_set#Continuous_.28smooth.29_coloring">smooth coloring</a>.</li>
<li>Let the user re-center the focus by dragging the image.</li>
<li>Speed things up on multi-core / multi-processor systems by using the fabulous <a href="http://openmp.org/wp/">openMP library</a> to parallelize your rendering loop. <em>Note:</em> this won’t be of much use on the virtual machine: even though your system likely does have more than one processor, the VM doesn’t emulate more than one very effectively (although it is capable of doing so).</li>
<li>Efficiency can be substantially improved for large numbers of iterations by detecting cycles. Unfortunately, there is a lot of rounding error in the floating point computation, so you will have to do something tricky to detect it. I’ve had success with using a <code>reinterpret_cast&lt;uint64_t*&gt;...</code>, but you have to be careful. And of course you have to know something about the <a href="http://en.wikipedia.org/wiki/Double_precision_floating-point_format">underlying format of doubles</a>. Finally, for small numbers of iterations, the overhead won’t make it a good trade-off unless you are clever about when to start looking for cycles.</li>
<li>When the number of iterations is high, it takes a while to draw the screen. Give the user more frequent status updates. Maybe show an animation of what is happening. You could quickly draw a “coarse” picture, and then fill it in, updating the window as you go.</li>
<li>Make the rendering loop run in a <a href="http://en.wikipedia.org/wiki/Thread_%28computer_science%29#Multithreading">background thread</a> so that the UI doesn’t sit there and drool while it is processing. If you combine this with the previous suggestion, then the user doesn’t have to wait so long to continue zooming. Qt provides a platform-independent interface to threading. Find it <a href="http://qt-project.org/doc/qt-4.8/threads.html">here</a>.</li>
<li>At some point, after a lot of zooming, the floating point datatype runs out of precision, and the numbers you need to distinguish are closer than the smallest thing that can be represented in a <code>double</code>. Use the fabulous <a href="http://gmplib.org/">GMP library</a> to work with arbitrary precision numbers so that you can zoom in arbitrarily far.</li>
</ol>
<p>Okay. I think I have given you enough to do. Finishing all those could keep you busy throughout the entire winter break. Or maybe even until you graduate.</p>
<!---}}-->
<!---{{ Submission proc-->
<h2 id="submission-procedure">Submission Procedure</h2>
<p>Your assignment will be graded by the TAs soon after the deadline, possibly during recitation (so you should be prepared to explain what you wrote!). For full credit, your project should</p>
<ol style="list-style-type: decimal">
<li>Produce output that passes a quick visual inspection;</li>
<li>Be hosted on bitbucket;</li>
<li>Have non-trivial contributions from each team member (this should be reflected in the commit logs).</li>
</ol>
<!---}}-->
<!---{{ Links-->
<!---}}-->
<!---
% vim:ff=unix:textwidth=78:foldmethod=marker:foldmarker={{,}}
-->
<div class="footnotes">
<hr />
<ol>
<li id="fn1"><p>By “diverge”, we mean that <span class="math inline">|<em>c</em><sub><em>n</em></sub>|</span> is unbounded. To be in the set, we don’t require that the sequence actually converges (this will only happen for the main “bulb”), just that the magnitude of the elements doesn’t blow-up.<a href="#fnref1">↩</a></p></li>
<li id="fn2"><p>It turns out that <em>every</em> affine linear transformation from 2 dimensional space is completely determined by what it does to the vectors <span class="math inline">(1, 0)</span>, <span class="math inline">(0, 1)</span>, and <span class="math inline">(0, 0)</span>. We can take a little shortcut, since we know we aren’t going to stretch the image, and we know we have to reflect over the <span class="math inline"><em>x</em></span>-axis, due to the screen to math coordinate conversion. Note that the factor of <span class="math inline">−1</span> attached to <span class="math inline"><em>s</em><em>y</em></span> is due to the fact that the screen coordinates in the <span class="math inline"><em>y</em></span>-direction increase as you move down, not up.<a href="#fnref2">↩</a></p></li>
</ol>
</div>
</body>
</html># Mandelbrot-Set-GUI
