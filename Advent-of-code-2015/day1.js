import input from './day1_data'

function myFunction() {
  let floor = 0
  let move = 0
  for (let i = 0; i < input.length; i++) {
    if (input.charAt(i) === "(") {
      floor++
    }
    else {
      floor--
    }
    if (floor === -1) {
      move = i
      break
    }
  }
  console.log(move)
}

myFunction()