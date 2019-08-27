#include <functional>
#include "base/logging.h"
#include "base/run_loop.h"
#include "base/bind.h"
#include "base/pickle.h"
#include "base/message_loop/message_loop.h"

void TestPickle(const base::RepeatingClosure& closure) {
  LOG(INFO) << __func__;
  base::Pickle pickle;
  pickle.WriteBool(true);
  pickle.WriteInt64(1024);
  pickle.WriteString("Hello, World");
  base::PickleIterator it(pickle);
  bool b;
  auto ret = it.ReadBool(&b);
  int64_t i;
  ret = it.ReadInt64(&i);
  std::string s;
  ret = it.ReadString(&s);
  LOG(INFO) << "b:" << b << ", i:" << i << ", s:" << s;
  closure.Run();
}

void TestBaseBind(int num) {
  std::function<int(int, int)> sum = [](int a, int b) { return a + b; };
  std::function<int(int)> plus1 = std::bind(sum, 1, std::placeholders::_1);
  LOG(INFO) << num << " plus 1 equals " << plus1(num);
}

int main(int argc, const char* argv[]) {
  base::MessageLoopForUI main_loop;
  base::RunLoop run_loop;
  auto quit_closure = run_loop.QuitClosure();

  main_loop.task_runner()->PostTask(FROM_HERE,
    base::BindOnce(&TestBaseBind, 3));

  main_loop.task_runner()->PostTask(FROM_HERE,
    base::BindOnce(&TestPickle, quit_closure));

  run_loop.Run();
  return 0;
}
