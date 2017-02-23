#ruby test_gen.rb {Matrix_size} {File_name}
def self.gen
  output = File.open( ARGV[1],"w" )
  for i in 0..ARGV[0].to_i
    for j in 0..ARGV[0].to_i
      if(rand(5) > 3)
        output << rand(2)
      else
        output << 0
      end
      output << ' '
    end
    output << "\n"
  end
  output.close
end

gen
