package define

import (
	"testing"
)

func TestPlayerQueue(t *testing.T) {
	var q PlayerQueue
	var i int32
	var loop int32 = 10
	for i = 0; i < loop; i++ {
		q.Push(i)
	}
	for i = 0; i < loop; i++ {
		if i != q.At(i) {
			t.Errorf("q.At(%d) != %v\n", i, q.At(i))
		}
	}
	// pop
	for i = 0; i < loop; i++ {
		if i != q.Pop().(int32) {
			t.Errorf("q.Pop != %d\n", i)
		}
	}
	// re push
	for i = 0; i < loop; i++ {
		q.Push(i)
	}
	for i = 0; i < loop; i++ {
		if i != q.At(i) {
			t.Errorf("q.At(%d) != %v\n", i, q.At(i))
		}
	}

}
