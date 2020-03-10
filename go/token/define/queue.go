package define

type Element interface{}

type Queue interface {
	// 返回一个位置标记
	Push(e Element)
	Pop() Element
	Size() int32
	Clear()
	Empty() bool
	At(pos int32) Element
}

type PlayerQueueSlice struct {
	nodes    []Element
	pushNums int32
	popNums  int32
}

func (p *PlayerQueueSlice) Push(e Element) {
	p.nodes = append(p.nodes, e)
	// ret := p.pushNums
	p.pushNums++
	// fmt.Printf("push:pushNums[%d] popNums[%d]\n", p.pushNums, p.popNums)
	// return ret
}

func (p *PlayerQueueSlice) Pop() Element {
	if len(p.nodes) == 0 {
		return nil
	}
	p.popNums++
	// fmt.Printf("pop:pushNums[%d] popNums[%d]\n", p.pushNums, p.popNums)
	node := p.nodes[0]
	p.nodes = p.nodes[1:]
	return node
}

func (p *PlayerQueueSlice) Size() int32 {
	return int32(len(p.nodes))
}

func (p *PlayerQueueSlice) Clear() {
	p.popNums = p.pushNums
	p.nodes = []Element{}
}

func (p *PlayerQueueSlice) Empty() bool {
	return p.Size() == 0
}

func (p *PlayerQueueSlice) At(pos int32) Element {
	if pos >= int32(len(p.nodes)) {
		return nil
	}
	return p.nodes[pos]
	// fmt.Printf("pos[%d]popNums[%d]\n", pos, p.popNums)
	// return p.nodes[pos-p.popNums]
}

// 优化版本，可以使用二维数组来模拟队列，每个队列假如长为1000， 每次分配1000，毁1000，减少内存释放次数
type PlayerQueueOptimize struct {
}

// 可以使用redis用来存放数据，这样服务崩溃了也不会丢失数据
type PlayerQueueRedis struct {
}

type PlayerQueue struct {
	PlayerQueueSlice
	// PlayerQueueOptimize
	// PlayerQueueRedis
}
