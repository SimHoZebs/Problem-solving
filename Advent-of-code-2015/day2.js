import input from './day2_data'

const emptySides = ["", "", ""]
const emptyAreas = ["", "", ""]

function myFunction() {
  let sides = emptySides;
  let areas = emptyAreas;
  let sidesIndex = 0;
  let total = 0

  for (let i = 0; i <= input.length; i++) {
    let char = input.charAt(i)

    if (char === "x") {
      sidesIndex++
      continue
    }
    else if (char === "\n") {
      console.log("sides " + sides)
      areas[0] = sides[0] * sides[1]
      areas[1] = sides[1] * sides[2]
      areas[2] = sides[0] * sides[2]

      const smallerArea = Math.min(areas[0], areas[1])
      const smallestArea = Math.min(smallerArea, areas[2])

      console.log("smallestArea " + smallestArea)

      total += 2 * (areas[0] + areas[1] + areas[2]) + smallestArea;

      sides = ["", "", ""]
      areas = ["", "", ""]
      sidesIndex = 0
    }
    else {
      sides[sidesIndex] += char
      console.log("char ", char)
    }
  }
  console.log(total)
}

myFunction()