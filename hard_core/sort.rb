#!/usr/bin/env ruby

raw = File.new("data.dat", "r")
pro = File.new("data.dat.1", "w")

raw.each_line do|line|
    vals = line.delete("\n").split("\t")
    pro.write( "%i\t" %vals[0].to_i + "%f\t" %vals[1].to_f + "%f\t" %vals[2].to_f + "%f\n" %vals[3].to_f )
end

raw.close
pro.close

