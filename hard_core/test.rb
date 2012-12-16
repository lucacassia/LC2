#!/usr/bin/env ruby

ARGV.each do|file|
    raw = File.new(file, "r")
    bin = File.new("data.dat.test", "w")

    min = 0.46
    max = 0.53
    num = 100
    width = (max-min)/num
    mean = Array.new num, 0
    size = 0

    raw.each_line do|line|
        vals =  line.delete("\n").split("\t")
        for i in 0..num-1
            if (min+i*width) < vals[1].to_f and vals[1].to_f <= (min+(i+1)*width)
                mean[i] += vals[2].to_f
                size += 1
            end
        end
    end

    for i in 0..num-1
        bin.write( "#{min+(i+0.5)*width}\t%.10e\n" %(num*mean[i]/size) )
    end

    raw.close
    bin.close

end
