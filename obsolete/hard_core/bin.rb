#!/usr/bin/env ruby

ARGV.each do|file|
    raw = File.new(file, "r")
    bin = File.new("bin.dat", "w")

    min = 0.0
    max = 5.0
    num = 40
    width = (max-min)/num
    freq = Array.new num, 0
    size = 0

    raw.each_line do|line|
        vals =  line.delete("\n").split("\t")
        mod2 = Math.sqrt(vals.map { |x| (x.to_f)**2 }.reduce(:+))
        for i in 0..num-1
            if (min+i*width) < mod2 and mod2 <= (min+(i+1)*width)
                freq[i] += 1
                size += 1
            end
        end
    end

    sum = 0.0
    for i in 0..num-1
        bin.write( "#{min+(i+0.5)*width}\t%.10e" %(freq[i]))
        bin.write( "\t%.10e\n" %(Math.sqrt(freq[i])) )
    end

    raw.close
    bin.close

end
