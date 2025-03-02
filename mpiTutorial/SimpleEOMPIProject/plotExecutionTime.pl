#!/usr/bin/perl

$toFind = "Tempo di esecuzione";
$tmpFile = "tmp.txt";
$resultDir = "TimeResults";
$exec = "OneMaxMpiEA";
@parallelTypes = ("seq", "eval", "multistart");
@processes = (1, 2, 4, 8, 16, 20);
$repetitions = 5;
# qx(make);

qx(mkdir -p $resultDir);

for $parallelType (@parallelTypes) {
    qx(echo "" > $resultDir/$parallelType);
    for $process (@processes) {
        next if ($process == 1 && $parallelType ne "seq");
        $totalTime = 0;
        for ($i = 0; $i < $repetitions; $i++) {
            qx(mpirun --oversubscribe -np $process $exec \@$exec.param --parallelType=$parallelType > $tmpFile);
            $output = qx(grep -i "$toFind" $tmpFile);
            if ($output =~ /.*(\d+\.\d+)/) {
                $totalTime += $1;
            }
        }
        $avgTime = $totalTime / $repetitions;
        qx(echo "$process $avgTime" >> $resultDir/$parallelType);
        last if ($process == 1 && $parallelType eq "seq");
    }
}

unlink $tmpFile;

$gnuplotScript = "$resultDir/plot.gnuplot";
if (!-e $gnuplotScript) {
    qx(echo "set terminal pngcairo enhanced font 'arial,10' size 800,600" > $gnuplotScript);
    qx(echo "set output '$resultDir/comparison.png'" >> $gnuplotScript);
    qx(echo "set title 'Confronto Tempo di Esecuzione'" >> $gnuplotScript);
    qx(echo "set xlabel 'Numero di Processi'" >> $gnuplotScript);
    qx(echo "set ylabel 'Tempo (s)'" >> $gnuplotScript);
    qx(echo "set key top right" >> $gnuplotScript);
    qx(echo "set grid" >> $gnuplotScript);
    qx(echo "set logscale x 2" >> $gnuplotScript);
    qx(echo "plot '$resultDir/seq' using 1:2 with linespoints title 'Sequential', '$resultDir/eval' using 1:2 with linespoints title 'Eval', '$resultDir/multistart' using 1:2 with linespoints title 'Multistart'" >> $gnuplotScript);
}

qx(gnuplot $gnuplotScript);
