# UtilityAI - Proof of concept

Utility AI is one of the most common approaches to AI systems in video games. Its concept is based on the evaluation of possible actions and then running the top scoring action.

Here I used Unreal Engine 4.22 top down template to implement my own AI system based on the Utility AI principles. The system relies on two main components – AIActions and DecisionMaker component.

The AIAction class connects a logic of given action (by reference to UGameplayAbility) with considerations and tag requirements used to calculate final Action Score. The considerations define which variable (such as health or distance to a target) has to be scored, how the variable should be normalized (e.g., to the optimal distance or range) and finally how to evaluate the consideration score based on chosen curve. The final Action Score is calculated based on all assigned considerations and tag requirements. All parts of this system can be implemented both in C++ as well as using Blueprints.

The DecisionMaker component is the main AI component that actually scores all potential actions of a given character and passes the top scoring action to a UAbilitySystemComponent.
