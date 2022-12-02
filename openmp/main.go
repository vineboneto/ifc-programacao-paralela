//go:build ignore

package main

import (
	"fmt"
	"math/rand"
	"time"
)

func timeTotal(start time.Time) {
	elapsed := time.Since(start)
	fmt.Printf("%s\n", elapsed)
}

func sum(s []int, c chan int) {

	sum := 0
	for _, v := range s {
		sum += v
	}
	c <- sum
}

func main() {

	TOTAL := 2000000
	TOTAL_THREADS := 16
	size := int(TOTAL / TOTAL_THREADS)
	arr := make([]int, TOTAL)
	ch := make(chan int)

	for i := 0; i < TOTAL; i++ {
		arr[i] = rand.Intn(50)
	}

	for i := 0; i < TOTAL_THREADS; i++ {
		go sum(arr[i*size:(i*size)+size], ch)
	}

	defer timeTotal(time.Now())
	sumParallel := 0
	for i := 0; i < TOTAL_THREADS; i++ {
		value := <-ch
		sumParallel = sumParallel + value
	}

	sumSerial := 0
	for i := 0; i < TOTAL; i++ {
		sumSerial = sumSerial + arr[i]
	}

	fmt.Printf("Sum serial %d\n", sumSerial)
	fmt.Printf("Sum parallel %d\n", sumParallel)
	fmt.Printf("Is equals %t\n", sumParallel == sumSerial)
}
