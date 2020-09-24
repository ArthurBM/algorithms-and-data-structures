// //Isso vai ficar feioso pois você ia ter que colocar o id do user e do channel
// void makeSubscription(string id, int score, Queue& userQueue, Queue &channelQueue) {
//         bool foundId = false;
//         if (userQueue.isEmpty()) {
//             userQueue.enqueue(id, score);
//         }
//         else {
//             Node *ptr = userQueue.getFront();
//             while (ptr->link != NULL)
//             {
//                 if(ptr->id == id) {
//                     ptr->score = score;
//                     foundId = true;
//                     // free(ptr);

//                 }
//                 else 
//                     ptr = ptr->link;
//             }
//             // free(ptr);
//             if (!foundId) {
//                 userQueue.enqueue(id,score);
//             }
//             // return false;
//         }
//         if (channelQueue.isEmpty()) {
//             channelQueue.enqueue(id, score);
//             cout << score << endl;
//         }
//         else {
//             Node *ptr = channelQueue.getFront();
//             while (ptr->link != NULL)
//             {
//                 if(ptr->id == id) {
//                     cout << score << endl;
//                     ptr->score = score;
//                     foundId = true;
//                     // free(ptr);

//                 }
//                 else 
//                     ptr = ptr->link;
//             }
//             // free(ptr);
//             if (!foundId) {
//                 channelQueue.enqueue(id,score);
//                 cout << score << endl;
//             }
//             // return false;
//         }
//     }