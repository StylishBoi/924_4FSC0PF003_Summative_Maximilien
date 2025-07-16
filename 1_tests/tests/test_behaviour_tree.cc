#include <gtest/gtest.h>
#include "behaviour_tree/behaviour_tree.h"

using namespace behaviour_tree;

// Helpers ---------------------------------------------------------------------------------------
Status simple_action (const bool check_conditions, const bool action_executed){
  Status status;

  if (check_conditions) {
    if (action_executed) {
      status = Status::kSuccess;
    }else {
      status = Status::kRunning;
    }
  }else {
    status = Status::kFailure;
  }

  std::cout << "Status : " << check_conditions << " : " << action_executed << " : " << status_to_str(status) << std::endl;
  return status;
};

auto AlwaysSuccess = [](){return Status::kSuccess;};
auto AlwaysRunning = [](){return Status::kRunning;};
auto AlwaysFailed = [](){return Status::kFailure;};

//Test if the leafs can have different status
TEST(BehaviourTree, leaf_basics) {

  Leaf leaf_q(AlwaysSuccess);
  EXPECT_EQ(leaf_q.Tick(), Status::kSuccess);

  Leaf leaf_b(AlwaysRunning);
  EXPECT_EQ(leaf_b.Tick(), Status::kRunning);

  Leaf leaf_c(AlwaysFailed);
  EXPECT_EQ(leaf_c.Tick(), Status::kFailure);

}

//Test if NoLoop is really empty at inilitation
TEST(BehaviourTree, no_loop_empty) {
  NoLoop no_loop;

  no_loop.Tick();
  EXPECT_EQ(no_loop.Tick(), Status::kFailure);

}

//Test if NoLoop works with one child
TEST(BehaviourTree, no_loop_one_child) {

  bool check_conditions = false;
  bool action_executed = false;
  NoLoop no_loop;

  no_loop.Add(std::make_unique<Leaf>([&]{return simple_action(check_conditions, action_executed);}));

  EXPECT_EQ(no_loop.Tick(), Status::kFailure);

  check_conditions = true;
  EXPECT_EQ(no_loop.Tick(), Status::kRunning);

  action_executed = true;
  EXPECT_EQ(no_loop.Tick(), Status::kSuccess);
  EXPECT_EQ(no_loop.Tick(), Status::kSuccess);

}

TEST(BehaviourTree, no_loop_multiple_children) {
  //In this test, NoLoop will stop on the first failure
  NoLoop no_loop_failure;

  no_loop_failure.Add(std::make_unique<Leaf>([&]{return simple_action(false, false);}));
  no_loop_failure.Add(std::make_unique<Leaf>([&]{return simple_action(true, false);}));
  no_loop_failure.Add(std::make_unique<Leaf>([&]{return simple_action(true, true);}));

  EXPECT_EQ(no_loop_failure.Tick(), Status::kFailure);

  //In this test, NoLoop will go through all the running phases before landing on running status
  NoLoop no_loop_running;

  no_loop_running.Add(std::make_unique<Leaf>([&]{return simple_action(true, true);}));
  no_loop_running.Add(std::make_unique<Leaf>([&]{return simple_action(true, true);}));
  no_loop_running.Add(std::make_unique<Leaf>([&]{return simple_action(true, false);}));

  EXPECT_EQ(no_loop_running.Tick(), Status::kRunning);

  //In this test, NoLoop will go through all the success phases and be forced to return success in the end
  NoLoop no_loop_success;

  no_loop_success.Add(std::make_unique<Leaf>([&]{return simple_action(true, true);}));
  no_loop_success.Add(std::make_unique<Leaf>([&]{return simple_action(true, true);}));
  no_loop_success.Add(std::make_unique<Leaf>([&]{return simple_action(true, true);}));

  EXPECT_EQ(no_loop_success.Tick(), Status::kSuccess);
}

//Check if a selector works with one child
TEST(BehaviourTree, selector_one_child) {
  Selector selector_1;
  selector_1.Add(std::make_unique<Leaf>(AlwaysSuccess));
  EXPECT_EQ(selector_1.Tick(), Status::kSuccess);

  Selector selector_2;
  selector_2.Add(std::make_unique<Leaf>(AlwaysRunning));
  EXPECT_EQ(selector_2.Tick(), Status::kRunning);

  Selector selector_3;
  selector_3.Add(std::make_unique<Leaf>(AlwaysFailed));
  EXPECT_EQ(selector_3.Tick(), Status::kFailure);
}

TEST(BehaviourTree, selector_multiple_children) {

  //Selector will tick until finding a running OR success status
  Selector multiple_run;

  multiple_run.Add(std::make_unique<Leaf>(AlwaysFailed));
  multiple_run.Add(std::make_unique<Leaf>(AlwaysRunning));
  multiple_run.Add(std::make_unique<Leaf>(AlwaysSuccess));

  EXPECT_EQ(multiple_run.Tick(), Status::kRunning);

  //Selector will tick until finding a success OR success status
  Selector multiple_success;

  multiple_success.Add(std::make_unique<Leaf>(AlwaysFailed));
  multiple_success.Add(std::make_unique<Leaf>(AlwaysFailed));
  multiple_success.Add(std::make_unique<Leaf>(AlwaysSuccess));

  EXPECT_EQ(multiple_success.Tick(), Status::kSuccess);

  //Selector will tick and return failure as none of his children succeed or run
  Selector multiple_failure;

  multiple_failure.Add(std::make_unique<Leaf>(AlwaysFailed));
  multiple_failure.Add(std::make_unique<Leaf>(AlwaysFailed));
  multiple_failure.Add(std::make_unique<Leaf>(AlwaysFailed));

  EXPECT_EQ(multiple_failure.Tick(), Status::kFailure);
}
