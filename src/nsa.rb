require 'csv'

##################################################################
# pRNG based on http://www.cs.wm.edu/~va/software/park/park.html
##################################################################

$MODULUS    = 2147483647
$MULTIPLIER = 48271
$DEFAULT    = 123456789

$seed = $DEFAULT

def Random()
  $Q = $MODULUS / $MULTIPLIER
  $R = $MODULUS % $MULTIPLIER

  t = $MULTIPLIER * ($seed % $Q) - $R * ($seed / $Q)
  if t > 0
    $seed = t
  else
    $seed = t + $MODULUS
  end
  return ($seed * 1.0) / ($MODULUS * 1.0)
end

def random_vector(minmax)
  return Array.new(minmax.length) do |i|
    # minmax[i][0] + ((minmax[i][1] - minmax[i][0]) * rand())
    minmax[i][0] + ((minmax[i][1] - minmax[i][0]) * Random())
  end
end

def euclidean_distance(c1, c2)
  sum = 0.0
  c1.each_index {|i| sum += (c1[i]-c2[i])**2.0}
  return Math.sqrt(sum)
end

def contains?(vector, space)
  vector.each_with_index do |v,i|
    return false if v<space[i][0] or v>space[i][1]
  end
  return true
end

def matches?(vector, dataset, min_dist, printDist = false) # false
  dataset.each do |pattern|
    dist = euclidean_distance(vector, pattern[:vector])
    puts "#{dist} / #{min_dist}" if printDist == true
    return true if dist <= min_dist
  end
  return false
end

def generate_detectors(max_detectors, search_space, self_dataset, min_dist, generation = 0)
  detectors = []
  contador = 1
  puts "Generating Detectors"
  begin
    detector = {:vector => random_vector(search_space)}
    if !matches?(detector[:vector], self_dataset, min_dist)
      detectors << detector if !matches?(detector[:vector], detectors, 0.0)
      # puts "#{contador} / #{max_detectors}: #{detector}"
      puts "#{generation}: #{contador} / #{max_detectors}"
      contador += 1
    end
  end while detectors.size < max_detectors
  return detectors
end

def generate_self_dataset()
  self_space_trainning = CSV.read("dataset_trainning.csv")

  self_dataset = []

  self_space_trainning.each do |line|
      pattern = {}
      line_final = []

      line.each do |column|
          line_final << column.to_f
      end

      pattern[:vector] = line_final
      self_dataset << pattern

  end

  return self_dataset
end

def generate_self_dataset_for_testing()
  self_space_testing = CSV.read("dataset_testing.csv")

  self_dataset = []

  self_space_testing.each do |line|
      pattern = {}
      line_final = []

      line.each do |column|
          line_final << column.to_f
      end

      pattern[:vector] = line_final
      self_dataset << pattern

  end

  return self_dataset
end

def apply_detectors(detectors, self_dataset, min_dist)
  correct = 0
  trial = 1
  detected = []

  self_dataset.each do |linha|
    actual = matches?(linha[:vector], detectors, min_dist) ? "N" : "S"
    expected = matches?(linha[:vector], self_dataset, min_dist) ? "S" : "N"
    if actual != expected
      detected << trial
    end

    trial += 1
  end

  expected_detected = [11, 15, 23, 24, 25, 30, 37, 55, 72]
  # puts "Done. Result: #{detected.size}/#{trial-1}\nDetected: #{detected.to_s}\nExpected: #{expected_detected.to_s}"
  # puts "Correta: #{(((expected_detected - detected).size - expected_detected.size)*-1) / expected_detected.size.to_f} / Incorreta: #{((detected - expected_detected).size) / expected_detected.size.to_f}"
  return "#{(((expected_detected - detected).size - expected_detected.size)*-1) / expected_detected.size.to_f}, #{((detected - expected_detected).size) / expected_detected.size.to_f}\n"
end

def execute(bounds, max_detect, min_dist, amount_of_proofs)
  general_results = ""

  amount_of_proofs.times do |proof|
    self_dataset_for_training = generate_self_dataset()
    generate_self_dataset_for_testing = generate_self_dataset_for_testing()
    detectors = generate_detectors(max_detect, bounds, self_dataset_for_training, min_dist, proof + 1)
    general_results += apply_detectors(detectors, generate_self_dataset_for_testing, min_dist)
  end

  puts general_results
end

if __FILE__ == $0
  # problem configuration
  problem_size = 44
  search_space = Array.new(problem_size) {[0.0, 1.0]}

  # algorithm configuration
  max_detectors = 1000
  min_dist = 3
  amount_of_proofs = 1

  # execute the algorithm
  execute(search_space, max_detectors, min_dist, amount_of_proofs)
end
